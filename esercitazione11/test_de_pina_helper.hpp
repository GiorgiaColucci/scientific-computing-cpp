#pragma once
#include <vector>
#include <set>
#include "edge.hpp"
template <typename T>
//trasformazione di un ciclo di nodi in un insieme di archi non orientati
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

/*trasformazione di una base di cicli minimi di nodi in un set di set di archi.
l'ordinamento interno è dato dall'operator overloading del minore per il confronto tra archi, l'ordinamento esterno è di tipo lessicografico
*/
template<typename U>
std::set<std::set<edge<U>>> normalize_basis (const std::vector<std::vector<U>>& basis) {
	std::set<std::set<edge<U>>> normalized_basis;
	for (const auto& cycle : basis) {
		normalized_basis.insert(normalize_cycle(cycle));
	}
	return normalized_basis;
}
