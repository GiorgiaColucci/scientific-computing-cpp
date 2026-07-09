#pragma once 
#include <set>
#include "graph.hpp"
#include "edge.hpp"

template <typename Node, typename Container>
graph<Node> graph_visit (const graph<Node>& G, 
                                    const Node& source, 
                                    Container& container) 
{
    graph<Node> tree;
    std::set<Node> visited;         
                       

    visited.insert(source);       
    container.put(source);        

    while(!container.empty()) {
        Node u=container.get();    
        for (const Node& w : G.neighbours(u)) {
            if (visited.find(w)==visited.end()) { 
                visited.insert(w); 
                container.put(w);
                tree.add_edge(edge<Node>(u,w));
            }
        }
    }
    return tree;
}