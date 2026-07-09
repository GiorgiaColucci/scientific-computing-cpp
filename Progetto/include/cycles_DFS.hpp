#pragma once
#include <vector>
#include <set>
#include <iostream>         // per std::cerr

#include "edge.hpp"
#include "graph.hpp"
#include "recursive_DFS.hpp"

// trovo il cammino da 'radice' a 'dest' usando una  Recursive_DFS; 
template <typename T>
bool dfs_path(const graph<T>& T_graph, const T& current, const T& dest, 
                std::set<T>& visited, std::vector<T>& path)
{
    visited.insert(current);
    path.push_back(current);

    if (current == dest) return true;        //destinazione raggiunta

    for (const T& v: T_graph.neighbours(current)) {
        if (visited.find(v) == visited.end()) {
            if (dfs_path(T_graph, v, dest, visited, path)) {
                return true;
            }
        }
    }

    path.pop_back();        //backtrack: questo ramo non porta a dest quindi lo rimuovo
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

    // Verifica che il numero di cicli sia corretto
    if ( k <= 0) { return {}; }

    std::vector<std::vector<T>> cicli(k);

    for (int j = 0; j < k; j++) {
        T a = coalbero[j].from();       // a < b per costruzione di edge<T>
        T b = coalbero[j].to();
        cicli[j] = find_path(T_graph, a , b);       // chiusura implicita b --> a

        // Verifica che il cammino sia stato trovato 
        if (cicli[j].empty()) {
            std::cerr << "ERRORE: cammino non trovato tra " << a << " e " << b << "\n";
            return {};
        }
    }
    
    return cicli;
}
