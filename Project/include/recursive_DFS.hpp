#pragma once
#include <vector>
#include <set>
#include <iostream>         // for std::cerr

#include "edge.hpp"
#include "graph.hpp"

/*
Recursive_DFS;
Uses a scheme where, for each node:
1. mark it as visited
2. look at its neighbors
3. if a neighbor is not visited:
	• add the edge to the DFS tree
	• call DFS on that neighbor (recursive step)
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
			dfs_visit(G, v, visited, result);		// recursive call
		}
	} 
}

template <typename T>
graph<T> recursive_dfs(const graph<T>& G, const T& node)
{
    graph<T> result; 
	std::set<T> visited;
	
	dfs_visit(G, node, visited, result);		// recursive function
	
	return result;
}
