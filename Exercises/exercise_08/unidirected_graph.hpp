#pragma once
#include "unidirected_edge.hpp"

#include <set>
#include <map>
//ALGORITHM????
#include <optional> //per sollevare eccezioni con std::nullopt
#include <iterator> //per std::distance e std::advance
#include <iostream>

/* 

Non devo usare add_node(), quindi devo fare una struttura guidata dagli archi. I nodi vengono aggiunti implicitamente all'inserimento degli archi. Struttura guidata dagli archi.
Strutture usate:
• edges --> std::set<unidirected_edge<T>> 			per avere archi ordinati senza duplicati; set di 		archi non diretti 
• nodes --> std::set<T>								per avere nodi ordinati senza duplicati
• adj --> std::map<T, std::set<T>>					lista di adiacenza per neighbours(); associo a ogni 	nodo l'insieme dei suoi vicini (che sono nodi quindi saranno un set); i due campi sono .first (nodo) e .second (set dei vicini).

I metodi che possono fallire (nodo/arco non trovato, indice fuori range) restituiscono std::optional; poi bisogna controllare con .has_value() prima di usare .value() nel main.

*/ 

template <typename T>
class unidirected_graph {
	std::set<unidirected_edge<T>> 	edges_;		//essendo un set, usa automaticamente la funzione operator< definita nello unidirected_edge.hpp perchè il set ha bisogno di sapere come ordinare gli elementi
	std::set<T> 					nodes_;
	std::map<T, std::set<T>> 		adj_;		//con adj_[u] accedo alla lista di adiacenza di u, cioè allo std::set connesso a u; se il nodo u non c'è, il [] lo crea e assegna un valore di default
	
public:
	/* Costruttore di default */
	unidirected_graph() = default; 		//quando chiamo default, mi costruisce tre strutture dati vuote per edges_, nodes_, e adj_
	
	/* Costruttore di copia */
	unidirected_graph(const unidirected_graph& other) : 
		edges_(other.edges_), nodes_(other.nodes_), adj_(other.adj_) {}
		
		
	/* add_edge() che permetta di aggiungere un arco al grafo; devo aggiornare edges_, aggiornare nodes_, aggiornare adj_ in entrambe le direzioni, cioè per u e v; tutto questo lo faccio usando le funzioni fornite dalla standard library per set e map */
	void add_edge(T u, T v) {
		unidirected_edge<T> e(u,v);		//per come ho definito unidirected_edge, qui mi ordina già l'arco con il primo nodo (from) più piccolo
		
		edges_.insert(e);
		
		nodes_.insert(u);
		nodes_.insert(v);
		
		adj_[u].insert(v);
		adj_[v].insert(u);	
	}
	
	
	/* neighbours() che, dato un nodo, restituisce i suoi vicini (quindi un set) */
	std::optional<std::set<T>> neighbours(const T& node) const {
		auto it = adj_.find(node); 
		if (it == adj_.end()) {
			std::cout << "neighbours: nodo non presente nel grafo \n"; //nodo non trovato --> "vuoto"
			return std::nullopt;		//nel main devo mettere if has_value()
		}
		return it -> second; //-> dereferenzia l'iteratore it e accede al campo, cioè come (*it).second; quindi restituisce la copia del set dei vicini 	
	}
	
	
	/* all_edges() che restituisce tutti gli archi; li restituisco in un set */
	const std::set<unidirected_edge<T>>& all_edges() const { 
		return edges_;
	}
	
	
	/* all_nodes() che restituisce tutti i nodi; li restituisco in un set */
	const std::set<T>& all_nodes() const { 
		return nodes_;
	}
	
	
	/* edge_number() che, dato un arco, ne restituisce la sua numerazione all’interno
del grafo, partendo da 0; da nullopt se l'arco non è presente nel grafo */
	std::optional<int> edge_number(const unidirected_edge<T>& e) const {
		auto it = edges_.find(e); 
		if (it == edges_.end()) {
			std::cout << "edge_number: arco non presente nel grafo \n"; //arco non trovato --> "vuoto"
			return std::nullopt;
		}
		return static_cast<int>(std::distance(edges_.begin(),it));	//metto static_cast cosi restituisce un int e converte da formato lungo (64 bit) a 32 bit evitando il warning di narrowing (troncamento implicito)
	}
	
	
	/* edge_at() che, dato un numero d’arco, restituisce il corrispondente oggetto arco
all’interno del grafo; restituisce nullopt se l'arco ha indice fuori range */
	std::optional<unidirected_edge<T>> edge_at(int index) const {
		if (index < 0 || index >= static_cast<int>(edges_.size())) 	//uso static_cast per far restituire int e avere un confronto equo
		{
			std::cout << "edge_at: indice fuori range \n";
			return std::nullopt;
		}
		auto it = edges_.begin();
		std::advance(it, index);
		return *it;	//restituisce il valore puntato da it, che è ciò che è nell'indice fornito, cioè l'arco giusto
	}
	
	
	/* operator-(), che permette di calcolare la differenza tra due grafi: dati G e G', la differenza G− G' è data dagli archi presenti in G e non presenti in G' */
	unidirected_graph operator-(const unidirected_graph& other) const {
		unidirected_graph result;
		for (const auto& e : edges_) {
			if (other.edges_.find(e) == other.edges_.end()) 	//ho trovato un arco che sta nel grafo attuale *this ma non sta in other (in other ho end come ritorno)
			{	result.add_edge(e.from(), e.to());		}
		} 
		return result;
	}
	
};
	
/*operatore di stampa del grafo, come funzione libera, fuori dalla classe; metto lo stesso template T della classe e accedo ai membri pubblici; */
template <typename T>
std::ostream& operator<<(std::ostream& os, const unidirected_graph<T>& g) {
	os << "Nodi: { ";
	for (const auto& n : g.all_nodes()) { os << n << " "; }
	os << "}\n";
	os << "Archi: { ";
	for (const auto& e : g.all_edges()) { os << e << " "; }
	os << "}";	
	return os;
}
