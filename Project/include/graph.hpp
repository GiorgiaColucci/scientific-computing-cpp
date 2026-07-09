#pragma once
#include "edge.hpp"
#include <map>
#include <set>
#include <vector>
#include <algorithm>
template <typename T>
class graph {
	std::map<T, std::set<T>> adj;
	std::vector<edge<T>> E;
	public:
		graph() = default;
		
		graph (const graph & other) = default;
		
		void add_edge(const edge<T> & e) {
			adj[e.from()].insert(e.to());
			adj[e.to()].insert(e.from());
			E.push_back(e);
			std::sort(E.begin(), E.end());
			auto it = std::unique(E.begin(), E.end());
			E.erase (it, E.end());
		}
		
		const std::vector<edge<T>>& all_edges() const {
			return E;
		}
		
		const std::set<T>& neighbours(const T& v) const {
			return adj.at(v);
		}
		
		std::set<T> all_nodes() const{
			std::set<T> res;
			for (const auto& p: adj) {
				res.insert(p.first);
			}
			return res;
		}
		
		int edge_number(const edge<T>& e) const {
			for (size_t i = 0; i < E.size(); i++) {
				if (E[i] == e) {
					return i;
				}
			}
			return -1;
		}
		
		edge<T> edge_at(int i) const {
			return E.at(i);
		}
		
		graph operator-(const graph& G_2) const {
			graph G_f;
			for (size_t i = 0; i < E.size(); i++) {
				int n = G_2.edge_number(E[i]);
				if (n == -1) {
					G_f.add_edge(E[i]);
				}
			}
			return G_f;
		}
};