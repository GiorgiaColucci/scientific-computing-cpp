#pragma once
#include <vector>
#include <map>
#include "edge.hpp"
#include "graph.hpp"
#include "lifo.hpp"
#include "graph_visit.hpp"
#include "dijkstra.hpp"
#include "dot_prod.hpp"
#include "binary_diff.hpp"
template <typename T>
std::vector<std::vector<T>> De_Pina(const graph<T>& G) {
	// 1. Estrazione del primo arco per inizializzare la visita
	edge<T> first_edge = G.edge_at(0);
	T first_node = first_edge.from();

	// 2. Creazione dell'albero di ricoprimento T e del coalbero C
	lifo<T> q;
	graph<T> T_graph = graph_visit(G, first_node, q);
	graph<T> C_graph = G - T_graph;

	const std::vector<edge<T>>& E = G.all_edges();
	std::set<T> V = G.all_nodes();
	const int m = static_cast<int>(E.size());
	const int n = static_cast<int>(V.size());
	const int k = m - n + 1;		// numero di cicli fondamentali (dimensione base)

	// Verifica che il numero di cicli sia corretto
    if ( k <= 0 ) { return {}; }

	// 3. Inizializzazione della base S_big
	std::vector<std::vector<bool>> S_big(k);
	for (int i = 0; i < k; i++) {
		S_big.at(i).resize(m);
		for (int j = 0; j < m; j++) {
			if (j == G.edge_number(C_graph.edge_at(i))) {
				S_big.at(i).at(j) = 1;
			}
			else {
				S_big.at(i).at(j) = 0;
			}
		}
	}

	// 4. Mappatura dei nodi in ID numerici per la costruzione di G_prime (G')
	std::map<T, int> node_to_id;
	std::vector<T> id_to_node(n);
	int v_index = 0;
	for (const T& v : V) {
		id_to_node.at(v_index) = v;
		node_to_id[v]= v_index;		//qui va bene [] perchè è una mappa
		v_index++;
	}

	std::vector<std::vector<T>> B(k);

	for (int i = 0; i < k; i++) {
		graph<int> G_prime;

		// 5. Costruzione del grafo ausiliario sdoppiato G_prime (G')
		for (const edge<T>& e : E) {
			T u = e.from();
			T v = e.to();
			int u_minus = node_to_id[u];
			int v_minus = node_to_id[v];

			if (S_big.at(i).at(G.edge_number(e)) == 1) {
				edge<int> edge_1(u_minus, v_minus + n);
				edge<int> edge_2(u_minus + n, v_minus);
				G_prime.add_edge(edge_1);
				G_prime.add_edge(edge_2);
			}
			else {
				edge<int> edge_1(u_minus, v_minus);
				edge<int> edge_2(u_minus + n, v_minus + n);
				G_prime.add_edge(edge_1);
				G_prime.add_edge(edge_2);
			} 
		}

		std::vector<edge<int>> E_prime = G_prime.all_edges();
		std::map<edge<int>, double> W;
		for (const edge<int>& e_prime : E_prime) {
			W[e_prime] = 1.0;
		}

		std::vector<bool> C_best(m);
		int best_count_ones = m + 1; //inizializzato come caso peggiore, + 1 per evitare loop infinito nel caso H del test

		// 6. Ricerca del ciclo più corto (Shortest Odd Cycle) (dijkstra)
		for (const T& v : V){
			int v_minus = node_to_id[v];

			std::pair<std::map<int, double>, std::map<int, std::optional<int>>>SSSP = Dijkstra(G_prime, v_minus, W);
			std::map<int, double> distances = SSSP.first;
			std::map<int, std::optional<int>> predecessors = SSSP.second;

			double dist_v_minus_to_v_plus = distances[v_minus + n];
			if (dist_v_minus_to_v_plus == -1.0) {		// -1 funge da sentinella "infinito"
				continue;
			}
			
			// Ricostruzione del percorso
			std::vector<int> current_path;
			current_path.reserve(dist_v_minus_to_v_plus);
			int current_node = v_minus + n;

			while (current_node != v_minus) {
				current_path.push_back(current_node);
				current_node = predecessors[current_node].value();
			}
			current_path.push_back(v_minus); //alternativa alla gestione dell'eccezione std::bad_optional_access;
			
			std::reverse(current_path.begin(), current_path.end());
			
			std::vector<bool> C(m);
			for (size_t l = 0; l < current_path.size() - 1; l++) {
				T u_in = id_to_node.at(current_path[l] % n);		// % n mappa v+ al nodo originale
				T v_in = id_to_node.at(current_path[l+1] % n);
				
				edge<T> e_current(u_in,v_in);
				int edge_num = G.edge_number(e_current);
				C.at(edge_num)= (C.at(edge_num) + 1) % 2;
			}

			int current_count_ones = 0;
			for (const bool b : C) {
				if (b==1) {
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
			int dot_prod_value = dot_prod(S_big.at(j), C_best);
			if (dot_prod_value == 1) {
				S_big.at(j) = binary_diff(S_big.at(j), S_big.at(i));
			}
		}

		// 8. Ricostruzione topologica del ciclo per l'output in B[i]
		std::vector<T> C_return;
		int index_primo = 0; //scelto il valore minimo possibile
		bool flag_primo_trovato = false;
		const int C_len = static_cast<int>(C_best.size());
		T root_C;
		T current_node_C;

		for (int i_C = 0; i_C < C_len; i_C++) {
			if (flag_primo_trovato == false && C_best.at(i_C) == 1) {
				edge<T> e = G.edge_at(i_C);
				T v_from = e.from();
				T v_to = e.to();
				C_return.push_back(v_from);
				C_return.push_back(v_to);
				flag_primo_trovato = true;
				index_primo = i_C;
				C_best.at(i_C) = 0;
				root_C = v_from;
				current_node_C = v_to;
				break;
			}
		}

		while (current_node_C != root_C) {
			for (int i_C_2 = index_primo; i_C_2 < C_len; i_C_2++) {
				if (C_best.at(i_C_2) == 1) {
					edge<T> e = G.edge_at(i_C_2);
					T v_from = e.from();
					T v_to = e.to();
					
					if (v_from == current_node_C) {  //considerando che non ci sia un arco da un nodo a se stesso
						C_return.push_back(v_to);
						C_best.at(i_C_2) = 0;
						current_node_C = v_to;
						break;
					}
					else if (v_to == current_node_C) {
						C_return.push_back(v_from);
						C_best.at(i_C_2) = 0;
						current_node_C = v_from;
						break;
					}
				}
			}
		}
		B.at(i) = C_return;	
	}
	return B;
}	