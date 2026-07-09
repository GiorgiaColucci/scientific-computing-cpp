#pragma once
#include <vector>
#include <set>
#include <iostream>         // for std::cerr

#include "edge.hpp"
#include "graph.hpp"
#include "recursive_DFS.hpp"

// find the path from 'root' to 'dest' using a Recursive_DFS; 
template <typename T>
bool dfs_path(const graph<T>& T_graph, const T& current, const T& dest, 
                std::set<T>& visited, std::vector<T>& path)
{
    visited.insert(current);
    path.push_back(current);

    if (current == dest) return true;        //destination reached

    for (const T& v: T_graph.neighbours(current)) {
        if (visited.find(v) == visited.end()) {
            if (dfs_path(T_graph, v, dest, visited, path)) {
                return true;
            }
        }
    }

    path.pop_back();        // backtrack: this branch does not lead to dest, so remove it
    return false;
}

template <typename T>
std::vector<T> find_path(const graph<T>& T_graph, const T& radice, const T& dest) 
{
    std::set<T> visited;
    std::vector<T> path;
    if (!dfs_path(T_graph, radice, dest, visited, path)) { return {}; }
    return path;
} 


template <typename T>
std::vector<std::vector<T>> cicli_DFS(const graph<T>& G) {
    T nodo_radice = G.edge_at(0).from();
    graph<T> T_graph = recursive_dfs(G, nodo_radice);

    const graph<T> C_graph = G - T_graph;
    const std::vector<edge<T>> coalbero = C_graph.all_edges();
    const int k = static_cast<int>(coalbero.size());

    // Check that the number of cycles is correct
    if ( k <= 0) { return {}; }

    std::vector<std::vector<T>> cicli(k);

    for (int j = 0; j < k; j++) {
        T a = coalbero[j].from();       // a < b by construction of edge<T>
        T b = coalbero[j].to();
        cicli[j] = find_path(T_graph, a , b);       // implicit closure b --> a

        // Check that the path was found
        if (cicli[j].empty()) {
            std::cerr << "ERRORE: cammino non trovato tra " << a << " e " << b << "\n";
            return {};
        }
    }
    
    return cicli;
}
