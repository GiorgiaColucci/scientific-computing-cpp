#pragma once
#include <vector>
#include <set>
#include "edge.hpp"
template <typename T>

// transform a cycle of nodes into a set of undirected edges
std::set<edge<T>> normalize_cycle(const std::vector<T>& cycle) {
	std::set<edge<T>> edges;
	if (cycle.size() < 2) {
		return edges;
	}
	for (size_t i = 0; i < cycle.size() - 1; i++) {
		T u = cycle[i];
		T v = cycle[i+1];
		edge<T> e(u,v);
		edges.insert(e);
	}
	return edges;
}

/* 
transform a minimum cycle basis of nodes into a set of sets of edges.
the inner ordering comes from the overloaded less-than operator for comparing 
edges; the outer ordering is lexicographic
*/

template<typename U>
std::set<std::set<edge<U>>> normalize_basis (const std::vector<std::vector<U>>& basis) {
	std::set<std::set<edge<U>>> normalized_basis;
	for (const auto& cycle : basis) {
		normalized_basis.insert(normalize_cycle(cycle));
	}
	return normalized_basis;
}
