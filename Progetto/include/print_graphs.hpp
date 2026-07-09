#pragma once
#include "edge.hpp"
#include "graph.hpp"
#include "print_edges.hpp"
#include "graph_construction.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

template <typename T>
void print_graphviz(const graph<T>& G, const std::map<edge<T>, edge_data>& edge_map) {
    std::cout << "graph G {" << "\n";
    
    std::vector<edge<T>> E = G.all_edges(); 
    
    for (const edge<T>& e : E) { 
        const auto& data = edge_map.at(e);
        // Niente punto e virgola prima della parentesi quadra
        std::cout << "    " << e.from() << " -- " << e.to() 
                  << " [label=\"" << data.nome << ": "<< data.valori << "\"];\n";
    }
    
    std::cout << "}" << "\n";
}

template <typename T>
void to_dot(const graph<T>& G, const std::string& file, const std::map<edge<T>, edge_data>& edge_map) {
    std::ofstream out(file);
    out << "graph G {" << "\n";

    for (const T& v : G.all_nodes()) {
        out << "  \"" << v << "\"\n";
    }
    
    for (const edge<T>& e : G.all_edges()) {
        const auto& data = edge_map.at(e);
        out << "    " << e.from() << " -- " << e.to()
            << " [label=\"" << data.nome << " = " << data.valori << "\"];\n";
    }
    out << "}" << "\n";
}