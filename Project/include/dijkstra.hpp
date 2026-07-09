#pragma once
#include <queue>
#include <optional>
#include <map>
#include <set>
#include "edge.hpp"
#include "graph.hpp"
template <typename T>
std::pair<std::map<T, double>, std::map<T, std::optional<T>>> Dijkstra (const graph<T>& G, const T& s, const std::map<edge<T>, double>& W) {
	std::set<T> V = G.all_nodes();
	std::map<T, std::optional<T>> pred;
	std::map<T, double> dist;
	for (const T& nodo : V) {
		pred[nodo] = std::nullopt;
		dist[nodo] = -1.0;
	}
	pred.at(s) = s;
	dist.at(s) = 0;
	using pii = std::pair<double, T>;	
	std::priority_queue <pii, std::vector<pii>,std::greater<pii>> PQ;
	PQ.push({0.0, s});
	while (!PQ.empty()) {
		pii B = PQ.top();
		PQ.pop();
		double d_u = B.first;
		T u = B.second;
		if (d_u > dist[u]) {
			continue;
		}
		std::set<T> neigh = G.neighbours(u);
		for (const T& w : neigh) {
			edge<T> e(u,w);
			if (dist[w] == -1.0 || dist[w] > dist [u] + W.at(e)) {
				dist[w] = dist[u] + W.at(e);
				pred[w] = u;
				pii C(dist[w], w);
				PQ.push(C);
			}
		}
		
	}
	std::pair<std::map<T, double>, std::map<T, std::optional<T>>> res = {dist, pred};
	return res;
}