#pragma once 
#include <map>
#include <string>

#include "netlist_struct.hpp"
#include "edge.hpp"
#include "graph.hpp"

/* Build of graph G from the netlist.
Build of a map that associates each edge with an edge_data structure that in turn contains:
	- Type: the kind of component on that edge.
	- Value: the numeric value of the component on that edge.
	- Whether the canonical direction of the edge matches the direction in the netlist (true if n_min --> n_max).
	- Component name, for printing
*/

struct edge_data {
	TipoComponente tipologia;
	double valori;
	bool verso_positivo;
	std::string nome;
};


graph<int> costruisci_grafo(
	const Output& netlist,
	std::map<edge<int>, edge_data>& edge_data_map);