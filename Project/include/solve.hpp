#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <Eigen/Dense>

#include "lifo.hpp"
#include "edge.hpp"
#include "graph.hpp"
#include "graph_visit.hpp"
#include "netlist_struct.hpp"
#include "conjugate_gradient.hpp"
#include "graph_construction.hpp"

struct RisultatoCircuit {
    std::vector<std::string> nomi_resistori;
    std::vector<double>      tensioni;
    std::vector<double>      correnti;
};

/*
Circuit solver using the mesh current method. Uses the cycles provided by De Pina or DFS,
which return, for each cycle, the ordered sequence of nodes.
*/
template<typename T>
RisultatoCircuit circuit(
    const graph<T>& G, 
    const std::map<edge<int>, edge_data>&	  edge_data_map,
    const std::vector<std::vector<T>>&        cicli)
{   
    /* Take the minimum cycles from De Pina or DFS;
     cicli[j] = sequence of nodes of cycle j
     Cycle edges: (cicli[j][s], cicli[j][s+1]%L) for s = 0 ... L-1 */

    const std::vector<edge<T>>& E = G.all_edges();
    const int m = static_cast<int>(E.size());             // number of edges (components)
    const int k = static_cast<int>(cicli.size());         // number of independent meshes;

    if (k == 0) {
        std::cout << "Il circuito non presenta maglie chiuse da analizzare.\n";
        return {};
    }

    // Check for isolated nodes or other connected components via DFS: the graph must be connected
    lifo<T> stack_conn;   
    T radice_conn = G.edge_at(0).from();
    graph<T> T_conn = graph_visit(G, radice_conn, stack_conn);
    if (G.all_nodes().size() != T_conn.all_nodes().size()) {
        std::cerr << "ERRORE: il grafo non è connesso\n";
        return {}; 
    }

    /* Build the incidence matrix B (size m x k);
    B[i][j] = +1    if cycle j traverses edge i in the canonical direction from -> to
            = 0     if the edge does not belong to cycle j
            = -1    if cycle j traverses edge i in the opposite direction to -> from

    The rows for the voltage sources contribute zero to B^T * R * B because R is 0 on
    those rows, but they are included anyway for simplicity
    */
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(m, k);

    for (int j = 0; j < k; j++) {
        const std::vector<T>& cycle = cicli[j];
        const int L = static_cast<int>(cycle.size());

        for (int s = 0; s < L; s++) {
            T u = cycle[s];
            T v = cycle[(s+1)%L];           // closing edge : last --> first

            int id = G.edge_number(edge<T>(u,v));
            if (id == -1) continue;

            // Canonical direction: from() < to(); if u < v we traverse in the canonical direction (+1), otherwise (-1)
            B(id, j) = (u < v) ? +1.0 : -1.0;
        }
    }

    /* Build the resistance matrix (size m x m, diagonal)
    R[i][i] = the resistance value if the edge is a resistor, 0 otherwise
    */
    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(m, m);
    for (int i = 0; i < m; i++) {
        if (edge_data_map.at(E[i]).tipologia == TipoComponente::Resistore) {
            R(i, i) = edge_data_map.at(E[i]).valori;
        }   // voltage sources are treated as having zero resistance
    }

    /* Build the right-hand-side vector (size k)
    For each source in cycle j:
        dir = +1 if traversed in the canonical direction (smaller node --> larger node), -1 otherwise;
        verso_positivo[e] = true  --> canonical goes from + to - --> contribution -V (dir * (-1) * V) (+ is on the smaller-node side)
        verso_positivo[e] = false --> canonical goes from - to + --> contribution +V (dir * (+1) * V) (+ is on the larger-node side)
        verso_positivo therefore indicates where the terminal is located.

    The contribution depends on how the mesh crosses the source: while traversing the cycle, if we enter the source
    from the - node and exit from the +, it contributes +V; conversely, if we enter from the + node and exit from the -,
    it contributes -V.
    Recall that verso_positivo is true if the + terminal matches the canonical direction of the edge, i.e. from the
    smaller node to the larger node.
    */
    Eigen::VectorXd v = Eigen::VectorXd::Zero(k);
    for (int j = 0; j < k; j++) {
        const std::vector<T>& cycle = cicli[j];     
        const int L = static_cast<int>(cycle.size());

        for (int s = 0; s < L; s++) {
            T u_node = cycle[s];
            T v_node = cycle[(s+1)%L]; 
            int idx = G.edge_number(edge<T>(u_node, v_node));
            if (idx == -1) continue;
            if (edge_data_map.at(E[idx]).tipologia != TipoComponente::Generatore) continue;     // select only the voltage sources

            int dir = (u_node < v_node) ? +1 : -1;
            double sgn = edge_data_map.at(E[idx]).verso_positivo ? -1.0 : +1.0;
            v(j) += dir * sgn * edge_data_map.at(E[idx]).valori;
        }
    }

    // Report circuits with no sources (i_maglia = 0)
    const double tol = 1e-12;
    if (v.norm() < tol) {
        std::cout << "WARNING: nessun generatore nel circuito, tutte le correnti sono zero.\n";
    } 

    /* Linear system A = B^T * R * B, then A * i_maglia = v
    A is symmetric positive definite of size k x k */
    Eigen::MatrixXd A = B.transpose() * R * B;

    // Solve the linear system with the Conjugate Gradient method
    const int iter_max = 10000;
    GCDResult res_gcd = gradiente_cd(A, v, tol, iter_max);
    Eigen::VectorXd i_maglia = res_gcd.x;
   
    // Check whether the residual is too large: this would mean the system was not 
    // solved accurately enough (singular or ill-conditioned matrix)
    double norm_v = v.norm();
    double err = 0.0;
    if (norm_v < tol) {
	// avoid division by zero and assess stability using the absolute error
	err = (A * i_maglia -v).norm();
    }
    else {
	err = (A * i_maglia - v).norm()/ norm_v;
    }

    const double tol_check = 1e-9;
    if (err > tol_check) {
	std::cerr << "ERRORE: il sistema lineare non ha soluzione numericamente stabile" << "\n";
	return {};
    }

    /* Total current on each edge, obtained as the overlap of the mesh currents
    Voltages on each edge via Ohm's law: V = R * I  (V_tot = R * B * i_maglia)
    */
    Eigen::VectorXd I_tot = B * i_maglia;   
    Eigen::VectorXd V_tot = R * I_tot;      // current on edge i in the canonical direction


    RisultatoCircuit r;
    for (int i = 0; i < m; i++) {
        if (edge_data_map.at(E[i]).tipologia == TipoComponente::Resistore) {
            r.nomi_resistori.push_back(edge_data_map.at(E[i]).nome);
            r.tensioni.push_back(V_tot(i));
            r.correnti.push_back(I_tot(i));
        }
    }
    return r;
}


// print result 
void stampa_risultati(const RisultatoCircuit& r)
{
    std::cout << "\n --- RISULTATI CIRCUITO ---\n";
    for (int i = 0; i < static_cast<int>(r.nomi_resistori.size()); i++) {
        std::cout << r.nomi_resistori[i]
                  << ": V = " << r.tensioni[i]
                  << " volts, I = " << r.correnti[i] << " amps\n";
    }
}

// initially the circuit function returned void and printed the results 
// directly to screen, but for the tests they need to be saved for later use