#pragma once 
#include "containers.hpp"
#include "unidirected_graph.hpp"
#include <set>
#include <queue>		//per Dijkstra, per priority queue

template<typename T, typename container>	//T è il tipo dei nodi
//uso l'implementazione dell'esercitazione precedente
unidirected_graph<T> graph_visit(const unidirected_graph<T>& G, const T& n, container& c) 	//G è il grafo, n è il nodo sorgente, c è il tipo di contenitore (s se lifo --> DFS, q se fifo --> BFS)
{
	// DEVO DEFINIRE s = lifo(), q = fifo()? No, perchè quello lo faccio nel main prima di chiamare graph_visit!! Qui devo solo usare la struttura che è gia dentro c 
	unidirected_graph<T> tree;		//albero vuoto
	
	std::set<T> visited;		//segna i nodi che sto man mano visitando; all'inizio è vuota, non serve mettere flag false o booleani, mi basta poi verificare se c'è il nodo dentro; uso questa struttura cosi evito ripetizioni  
	
	visited.insert(n); 		//segno la sorgente come visitata e la inserisco nel mio contenitore di visita
	c.put(n);			//in base a c, s viene inserita automaticamente in una stack o in una queue
	
	while(!c.empty())		//continua fin quando ci sono nodi da esplorare
	{
		T u = c.get();		//prendo il prossimo nodo
		
		/* neighbours restituisce std::optional<std::set<T>> --> lo devo controllare con .has_value */ 
		auto nb = G.neighbours(u);
		if (!nb.has_value()) continue;
		
		for (const auto& v : nb.value())		//prendo tutti i nodi collegati a u; 
		{
			if (visited.find(v) == visited.end())		//vedo se il vicino è gia stato visitato: std::set::find restituisce l'iteratore all'elemento richiesto se viene trovato, altrimenti restituisce l'iteratore a end() se non lo trova; IMP: end() è una posizione DOPO l'ultimo elemento, non l'ultimo elemento!!
			{ 	
				visited.insert(v); 		//segno il vicino come visitato
				c.put(v);				//metto il vicino nel container
				tree.add_edge(u,v);		//aggiungo l'arco all'albero
			}
		}
	} 
	
	return tree;
	
}


/*
Recursive_DFS; 
Uso una struttura in cui per ogni nodo:
1. lo segno visitato
2. guardo i vicini
3. se un vicino non è visitato:
	• aggiungo l'arco all'alber DFS
	• richiamo DFS sul vicino stesso (parte ricorsiva) 
*/
template <typename T> 
void dfs_visit(const unidirected_graph<T>& G, const T& n, std::set<T>& visited, unidirected_graph<T>& result)
{
	visited.insert(n);		// 1. 
	
	auto nb = G.neighbours(n);
	if (!nb.has_value()) return;
	
	for (const auto& v : nb.value())		// 2.
	{
		if (visited.find(v) == visited.end()) 		// 3.
		{
			result.add_edge(n,v);
			dfs_visit(G, v, visited, result);		//chiamata ricorsiva
		}
	} 
}

template <typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& G, const T& node)
{
	unidirected_graph<T> result; 
	std::set<T> visited;
	
	dfs_visit(G, node, visited, result);		// funzione ricorsiva
	
	return result;
}


/* 
Algoritmo di Dijkstra per grafi non pesati; non serve che in input fornisco la lista di adiacenza perchè per i vicini ho la funzione neighbours; non serve neanche che do come input n perchè nei cicli faccio direttamente all_nodes per iterare sui nodi;

Faccio una struct con nodo e distanza (tipi diversi) da inserire nell'algoritmo
*/
template <typename T>
struct nodo_pq {
	T nodo;
	int distanza;
	
	bool operator>(const nodo_pq& other) const {
		return distanza > other.distanza;
	}
};


template <typename T>		//passo dist e pred per riferimento con & senno modifico le copie locali
void dijkstra(const unidirected_graph<T>& G, const T& s, std::map<T, int>& dist, std::map<T, T>& pred)
{
	//dist[u] = distanza minima tra s a u (-1 se non raggiunto)
	
	for (const auto& node: G.all_nodes()) {
		pred[node] = node; 		//predecessori a nodo stesso come flag se non lo raggiungo
		dist[node] = -1; 		//distanze a -1 come sentinella
	}
	
	pred[s] = s;
	dist[s] = 0;
	
	/* Uso la priority queue della libreria standard; non inserisco subito tutti i nodi ma solo la sorgente; gli altri verranno aggiunti man mano, tanto i nodi con dist = -1 non vengono mai estratti prima di essere aggiornati nell'ultimo for.
	
	The priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.
A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> would cause the smallest element to appear as the top(). --- Preso dalla libreria standard
 */
	
	std::priority_queue < nodo_pq<T>, std::vector< nodo_pq<T> >, std::greater< nodo_pq<T>> >  pq;
	
	nodo_pq<T> inizio;
	inizio.nodo = s;
	inizio.distanza = 0;
	
	pq.push(inizio);
	
	while(!pq.empty()) {
		
		nodo_pq<T> attuale = pq.top(); 		//uso priority queue che ha top() e non front() e ho già greater
		pq.pop();
		
		T u = attuale.nodo;
		int d = attuale.distanza;
		
		// alternativa alla DecreaseKey: non posso aggiornare le priorità quindi evito di prendere nodi "vecchi" controllando le distanze
		if (d > dist[u]) { continue; }
		
		auto vicini_aus = G.neighbours(u);
		
		if (!vicini_aus.has_value())  { continue; }
		
		std::set<T> vicini = vicini_aus.value();
		
		for (const auto& w : vicini) {
			if (dist[w] == -1 || dist[w] > dist[u] + 1) // peso = 1
			{
				dist[w] = dist[u] + 1;
				pred[w] = u;
				
				nodo_pq<T> nuovo;
				nuovo.nodo = w;
				nuovo.distanza = dist[w];
				
				pq.push(nuovo);
			}
		}
		
	}
}

