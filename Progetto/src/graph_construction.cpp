#include "graph_construction.hpp"

// Solo implementazione
graph<int> costruisci_grafo(
    const Output&                           netlist, 
    std::map<edge<int>, edge_data>&    	    edge_data_map)

{
    graph<int> G;
    // Azzero all'inizio così che se chiamo la funzione più di una volta sulla stessa mappa, non tengo i dati vecchi
    edge_data_map.clear();
    
    for (const auto& c: netlist.componenti) {
        edge<int> e(c.n1, c.n2);        // In automatico l'arco viene memorizzato con from() = min(n1,n2); 

        G.add_edge(e);
        edge_data_map[e] = {c.tipo, c.valore, (c.n1 < c.n2), c.nome};
        /* Il terminale + del componente è c.n1: quindi, se n1<n2 allora il verso è positivo
        verso positivo servirà nel solve per assegnare il segno corretto alle tensioni dei generatori
	*/
    }

    return G;
}