#include "graph_construction.hpp"

// Implementation only 
graph<int> costruisci_grafo(
    const Output&                           netlist, 
    std::map<edge<int>, edge_data>&    	    edge_data_map)

{
    graph<int> G;
    // Clear at the start so that calling the function more than once on the same map does not keep stale data
    edge_data_map.clear();
    
    for (const auto& c: netlist.componenti) {
        edge<int> e(c.n1, c.n2);        // The edge is automatically stored with from() = min(n1,n2);
        G.add_edge(e);
        edge_data_map[e] = {c.tipo, c.valore, (c.n1 < c.n2), c.nome};
        /* The + terminal of the component is c.n1: therefore, if n1<n2 the direction is positive:
        this will be used in the solve function to assign the correct sign to the sources voltages 
	    */
    }

    return G;
}