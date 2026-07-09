#pragma once
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <algorithm>
#include <iostream>         // per std::cerr

#include "containers.hpp"
#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"
#include "graph.hpp"		// contiene sia graph_visit che dijkstra
#include "dot_prod.hpp"
#include "binary_diff.hpp"

// --------------------------------- find_path ---------------------------------
// trovo il cammino da 'radice' a 'dest' usando una  Recursive_DFS; 
template <typename T>
bool dfs_path(const unidirected_graph<T>& T_graph, const T& current, const T& dest, 
                std::set<T>& visited, std::vector<T>& path)
{
    visited.insert(current);
    path.push_back(current);

    if (current == dest) return true;        //destinazione raggiunta

	auto opt_nb = T_graph.neighbours(current);
	if (opt_nb.has_value()) {
		for (const T& v: opt_nb.value()) {
			if (visited.find(v) == visited.end()) {
				if (dfs_path(T_graph, v, dest, visited, path)) {
					return true;
				}
			}
		}
	}

    path.pop_back();        //backtrack: questo ramo non porta a dest quindi lo rimuovo
    return false;
}

template <typename T>
std::vector<T> find_path(const unidirected_graph<T>& T_graph, const T& radice, const T& dest) 
{
    std::set<T> visited;
    std::vector<T> path;
    if (!dfs_path(T_graph, radice, dest, visited, path)) { return {}; }
    return path;
} 


// --------------------------------- cicli_DFS ---------------------------------
template <typename T>
std::vector<std::vector<T>> cicli_DFS(const unidirected_graph<T>& G) {
	auto opt_first_edge = G.edge_at(0);
	if (!opt_first_edge.has_value()) { return {}; }		// ritorna vettore vuoto se grafo non ha archi

    T nodo_radice = opt_first_edge.value().from();
    unidirected_graph<T> T_graph = recursive_dfs(G, nodo_radice);

    const unidirected_graph<T> C_graph = G - T_graph;
    const std::set<unidirected_edge<T>> coalbero = C_graph.all_edges();
    const int k = static_cast<int>(coalbero.size());

    // Verifica che il numero di cicli sia corretto
    if ( k <= 0) { return {}; }

    std::vector<std::vector<T>> cicli(k);

    for (const auto& edge_C : coalbero) {
        T a = edge_C.from();       // a < b per costruzione di edge<T>
        T b = edge_C.to();
        std::vector<T> path = find_path(T_graph, a , b);       // chiusura implicita b --> a

        // Verifica che il cammino sia stato trovato 
        if (path.empty()) {
            std::cerr << "ERRORE: cammino non trovato tra " << a << " e " << b << "\n";
            return {};
        }
		cicli.push_back(path);
    }
    
	return cicli;
}


// --------------------------------- De Pina ---------------------------------
template <typename T>
std::vector<std::vector<T>> De_Pina(const unidirected_graph<T>& G) {
	// 1. Estrazione del primo arco per inizializzare la visita
	auto opt_first_edge = G.edge_at(0);		
	if (!opt_first_edge.has_value()) {	
		return {};
	}
	unidirected_edge<T> first_edge = opt_first_edge.value();
	T first_node = first_edge.from();

	// 2. Creazione dell'albero di ricoprimento T e del coalbero C
	lifo<T> q;
	unidirected_graph<T> T_graph = graph_visit(G, first_node, q);
	unidirected_graph<T> C_graph = G - T_graph;

	const std::set<unidirected_edge<T>>& E = G.all_edges();		//const & + set + 
	const std::set<T>& V = G.all_nodes();		//&
	const int m = E.size();
	const int n = V.size();
	const int k = m - n + 1;		// numero di cicli fondamentali (dimensione base)

	// Verifica che il numero di cicli sia corretto
	if ( k<=0 ) return {}; 

	// 3. Inizializzazione della base S_big
	std::vector<std::vector<bool>> S_big(k, std::vector<bool>(m,0));	// metto la matrice con righe tutte a zero e di lunghezza m già nella definizione con il bool
	int s_index = 0; 
	for (const auto& e_C : C_graph.all_edges()) {
		auto opt_edge_num = G.edge_number(e_C);
		if (opt_edge_num.has_value() && s_index < k) {
			S_big[s_index][opt_edge_num.value()] = 1;
			s_index++;
		}
	}

	// 4. Mappatura dei nodi in ID numerici per la costruzione di G_prime (G')
	std::map<T, int> node_to_id;
	std::vector<T> id_to_node(n);
	int v_index = 0;
	for (const T& v : V) {
		id_to_node[v_index] = v;
		node_to_id[v]= v_index;
		v_index++;
	}

	std::vector<std::vector<T>> B(k);

	for (int i = 0; i < k; i++) {
		unidirected_graph<int> G_prime;

		// 5. Costruzione del grafo ausiliario sdoppiato G_prime (G')
		for (const unidirected_edge<T>& e : E) {
			T u = e.from();
			T v = e.to();
			int u_minus = node_to_id[u];
			int v_minus = node_to_id[v];

			auto opt_edge_num1 = G.edge_number(e);		
			if (!opt_edge_num1.has_value()) continue;

			// ricordare che n è il numero di nodi
			if (S_big[i][opt_edge_num1.value()] == 1) {
				// Arco "dispari" scambia di lato (da - a + e viceversa)
				G_prime.add_edge(u_minus, v_minus + n);	
				G_prime.add_edge(u_minus + n, v_minus);
			}
			else {
				// Arco "pari" rimane sullo stesso lato
				G_prime.add_edge(u_minus, v_minus);
				G_prime.add_edge(u_minus + n, v_minus + n);
			} 
		}

		std::vector<bool> C_best(m, 0);	
		int best_count_ones = m + 1; // inizializzato come caso peggiore > m 
		
		// 6. Ricerca del ciclo più corto (Shortest Odd Cycle)
		for (const T& v : V){
			int v_minus = node_to_id[v];

			std::map<int, int> distances;			// int e int perchè cosi ce l'ho nel dijkstra
			std::map<int, int> predecessors; 		// int e int perchè cosi ce l'ho nel dijkstra

			dijkstra(G_prime, v_minus, distances, predecessors);		// basta chiamarla e mi modifica le mappe dall'interno
			
			int dist_v_minus_to_v_plus = distances[v_minus + n];	

			// -1 funge da sentinella "infinito"
			if (dist_v_minus_to_v_plus == -1) {
				continue;
			}

			// Ricostruzione del percorso
			std::vector<int> current_path;
			current_path.reserve(dist_v_minus_to_v_plus + 1);
			int current_node = v_minus + n;

			while (current_node != v_minus) {
				current_path.push_back(current_node);
				current_node = predecessors[current_node];	
			}
			current_path.push_back(v_minus); //alternativa alla gestione dell'eccezione std::bad_optional_access;

			std::reverse(current_path.begin(), current_path.end());
			
			std::vector<bool> C(m, 0);		// 0 ?
			for (size_t l = 0; l < current_path.size() - 1; l++) {
				T u_in = id_to_node[current_path[l] % n];		// % n mappa v+ al nodo originale
				T v_in = id_to_node[current_path[l+1] % n];

				unidirected_edge<T> e_current(u_in,v_in);
				auto opt_edge_num2 = G.edge_number(e_current);

				if (opt_edge_num2.has_value()) {		
					int edge_num = opt_edge_num2.value();
					C[edge_num]= (C[edge_num] + 1) % 2;
				}
			}

			int current_count_ones = 0;
			for (const bool b : C) {
				if (b) {		// fa b == 1 in automatico
					current_count_ones++;
				}
			}

			if (current_count_ones < best_count_ones) {
				C_best = C;
				best_count_ones = current_count_ones;
			}
		}

		// 7. Aggiornamento degli altri insiemi S
		for (int j = i + 1; j < k; j++) {
			int dot_prod_value = dot_prod(S_big[j], C_best);
			if (dot_prod_value == 1) {
				S_big[j] = binary_diff(S_big[j], S_big[i]);
			}
		}

		// 8. Ricostruzione topologica del ciclo per l'output in B[i]
		std::vector<T> C_return;
		int index_primo = 0; //scelto il valore minimo possibile
		bool flag_primo_trovato = false;
		int C_len = C_best.size();
		T root_C;
		T current_node_C;

		for (int i_C = 0; i_C < C_len; i_C++) {
			if (flag_primo_trovato == false && C_best[i_C] == 1) {
				auto opt_e = G.edge_at(i_C);
				if (opt_e.has_value()) {		
					unidirected_edge<T> e = opt_e.value();
					T v_from = e.from();
					T v_to = e.to();
					C_return.push_back(v_from);
					C_return.push_back(v_to);
					flag_primo_trovato = true;
					index_primo = i_C;
					C_best[i_C] = 0;
					root_C = v_from;
					current_node_C = v_to;
					break;
				}
			}
		}

		while (current_node_C != root_C) {
			for (int i_C_2 = index_primo; i_C_2 < C_len; i_C_2++) {
				if (C_best[i_C_2] == 1) {
					auto opt_e1 = G.edge_at(i_C_2);
					if (!opt_e1.has_value()) continue;		

					unidirected_edge<T> e = opt_e1.value();
					T v_from = e.from();
					T v_to = e.to();
					
					if (v_from == current_node_C) {  //considerando che non ci sia un arco da un nodo a se stesso
						C_return.push_back(v_to);
						C_best[i_C_2] = 0;
						current_node_C = v_to;
						break;
					}
					else if (v_to == current_node_C) {
						C_return.push_back(v_from);
						C_best[i_C_2] = 0;
						current_node_C = v_from;
						break;
					}
				}
			}
		}
		B[i] = C_return;
	}
	return B;
}	
