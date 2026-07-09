#pragma once 
#include <map>
#include <string>

#include "netlist_struct.hpp"
#include "edge.hpp"
#include "graph.hpp"

/* Costruzione del grafo G a partire dalla netlist. 
Costruzione di una mappa che associa gli archi ad una struttura edge_data contenente a sua volta:
	- Tipologia che associa agli archi il tipo di componente che è su quell'arco.
	- Valori che associa a ogni arco il valore numerico del componente.
	- Controllo del verso canonico dell'arco coincide con il verso della netlist (true se n_min --> n_max).
	- Nome del componente, per la stampa
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