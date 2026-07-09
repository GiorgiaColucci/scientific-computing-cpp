#pragma once
#include <vector>
#include <set>
#include <iostream>         // per std::cerr

#include "edge.hpp"
#include "graph.hpp"

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
void dfs_visit(const graph<T>& G, const T& n, std::set<T>& visited, graph<T>& result)
{
	visited.insert(n);		// 1. 
	const std::set<T>& nb = G.neighbours(n);
	
	for (const auto& v : nb)		// 2.
	{
		if (visited.find(v) == visited.end()) 		// 3.
		{
			result.add_edge(edge<T>(n,v));
			dfs_visit(G, v, visited, result);		//chiamata ricorsiva
		}
	} 
}

template <typename T>
graph<T> recursive_dfs(const graph<T>& G, const T& node)
{
    graph<T> result; 
	std::set<T> visited;
	
	dfs_visit(G, node, visited, result);		// funzione ricorsiva
	
	return result;
}
