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
Risolutore del circuito con il metodo delle correnti di maglia. Usa i cicli forniti da De Pina o da DFS, 
che restituiscono per ogni ciclo la sequenza ordinata di nodi.
*/
template<typename T>
RisultatoCircuit circuit(
    const graph<T>& G, 
    const std::map<edge<int>, edge_data>&	  edge_data_map,
    const std::vector<std::vector<T>>&        cicli)
{   
    /* Prendo i cicli minimi con De Pina o DFS; 
     cicli[j] = sequenza di nodi del ciclo j
     Archi del ciclo: (cicli[j][s], cicli[j][s+1]%L) per s = 0 ... L-1 */

    const std::vector<edge<T>>& E = G.all_edges();
    const int m = static_cast<int>(E.size());             //numero di archi (componenti)
    const int k = static_cast<int>(cicli.size());         //numero di maglie indipendenti;

    if (k == 0) {
        std::cout << "Il circuito non presenta maglie chiuse da analizzare.\n";
        return {};
    }

    // Controllo di nodi isolati oppure altre componenti connesse, attraverso DFS: il grafo deve essere connesso
    lifo<T> stack_conn;   
    T radice_conn = G.edge_at(0).from();
    graph<T> T_conn = graph_visit(G, radice_conn, stack_conn);
    if (G.all_nodes().size() != T_conn.all_nodes().size()) {
        std::cerr << "ERRORE: il grafo non è connesso\n";
        return {}; 
    }

    /* Costruzione della matrice di incidenza B (dimensione m x k); 
    B[i][j] = +1    se il ciclo j percorre l'arco i nel verso canonico from -> to
            = 0     se l'arco non appartiene al ciclo j
            = -1    se il ciclo j percorre l'arco i nel verso opposto to -> from

    Le righe relative ai generatori contribuiscono zero in B^T * R * B perchè R è 0 su 
    quelle righe, ma le incluso lo stesso per semplicità
    */
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(m, k);

    for (int j = 0; j < k; j++) {
        const std::vector<T>& cycle = cicli[j];
        const int L = static_cast<int>(cycle.size());

        for (int s = 0; s < L; s++) {
            T u = cycle[s];
            T v = cycle[(s+1)%L];           //arco di chiusura: ultimo --> primo

            int id = G.edge_number(edge<T>(u,v));
            if (id == -1) continue;

            // Verso canonico: from() < to(); se u < v sto percorrendo nel verso canonico (+1), altrimenti (-1)
            B(id, j) = (u < v) ? +1.0 : -1.0;
        }
    }

    /* Costruzione della matrice delle resistenze (dimensione m x m, diagonale)
    R[i][i] = valore della resistenza se l'arco è un resistore, 0 altrimenti
    */
    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(m, m);
    for (int i = 0; i < m; i++) {
        if (edge_data_map.at(E[i]).tipologia == TipoComponente::Resistore) {
            R(i, i) = edge_data_map.at(E[i]).valori;
        }   //considero i generatori come a resistenza nulla
    }

    /* Costruzione del vettore dei termini noti (dimensione k)
    Per ogni generatore nel ciclo j: 
        dir = +1 se percorso nel verso canonico (nodo minore --> nodo maggiore), -1 altrimenti;
        verso_positivo[e] = true  --> canonico va da + a - --> contributo -V (dir * (-1) * V) (+ è dalla parte del nodo minore)
        verso_positivo[e] = false --> canonico va da - a + --> contributo +V (dir * (+1) * V) (+ è dalla parte del nodo maggiore)
        verso_positivo indica quindi dove si trova il terminale.

    Il contributo dipende da come la maglia attraversa il generatore: percorrendo il ciclo, se entro nel generatore 
    dal nodo - ed esco dal +, allora contribuisce con +V; viceversa, se entro nel generatore dal nodo + ed esco dal -, 
    allora contribuisce con -V. 
    Ricordare che verso_positivo è true se il terminale + coincide con il verso canonico dell'arco, cioè dal 
    nodo minore al nodo maggiore.
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
            if (edge_data_map.at(E[idx]).tipologia != TipoComponente::Generatore) continue;     // seleziono solo i generatori

            int dir = (u_node < v_node) ? +1 : -1;
            double sgn = edge_data_map.at(E[idx]).verso_positivo ? -1.0 : +1.0;
            v(j) += dir * sgn * edge_data_map.at(E[idx]).valori;
        }
    }

    // Segnalo che ci siano circuiti senza generatori (i_maglia = 0)
    const double tol = 1e-12;
    if (v.norm() < tol) {
        std::cout << "WARNING: nessun generatore nel circuito, tutte le correnti sono zero.\n";
    } 

    /* Sistema lineare A = B^T * R * B e poi A * i_maglia = v 
    A è simmetrica definita positiva di dimensione k x k) */
    Eigen::MatrixXd A = B.transpose() * R * B;

    // Risolvo il sistema lineare con Gradiente Coniugato
    const int iter_max = 10000;
    GCDResult res_gcd = gradiente_cd(A, v, tol, iter_max);
    Eigen::VectorXd i_maglia = res_gcd.x;
   
    // Controllo se il residuo è troppo grande: questo significherebbe che il sistema non è stato 
    // risolto con sufficiente precisione (matrice singolare o mal condizionata)
    double norm_v = v.norm();
    double err = 0.0;
    if (norm_v < tol) {
	//si evita la divisione per zero e si valuta la stabilità con l'errore assoluto
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

    /* Correnti totale su ogni arco ottenuta come sovrapposizione delle correnti di maglia
    Tensioni su ogni arco con legge di Ohm: V = R * I  (V_tot = R * B * i_maglia)
    */
    Eigen::VectorXd I_tot = B * i_maglia;   
    Eigen::VectorXd V_tot = R * I_tot;      // corrente su arco i nel verso canonico


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


// stampa risultato 
void stampa_risultati(const RisultatoCircuit& r)
{
    std::cout << "\n --- RISULTATI CIRCUITO ---\n";
    for (int i = 0; i < static_cast<int>(r.nomi_resistori.size()); i++) {
        std::cout << r.nomi_resistori[i]
                  << ": V = " << r.tensioni[i]
                  << " volts, I = " << r.correnti[i] << " amps\n";
    }
}

// inizialmente la funzione circuit restituiva void e stampava direttamente
// a schermo i risultati ma per i test ho bisogno di salvarli per usarli 