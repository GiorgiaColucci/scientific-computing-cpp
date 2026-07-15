#include "edge.hpp"
#include "graph.hpp"
#include "cycles_DFS.hpp"
 
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
 
/* Unit tests for cycles_DFS (fundamental cycles via DFS + cotree).

   We use the same graphs as test_de_pina.cpp, so that the two
   algorithms can be compared by eye on the same input:
     - F_albero:  4 nodes, 3 edges - a tree, no cycles
     - G_ciclico: F_albero + 2 edges - 2 fundamental cycles (= edges - nodes + 1)
*/
 
graph<int> F_albero;
graph<int> G_ciclico;
 
// Check that 'cycle' is a valid cycle in G: all nodes distinct and every 
// consecutive pair is an edge of G.
static bool is_ciclo_valido(const graph<int>& G, const std::vector<int>& cycle)
{
    if (cycle.size() < 3) {
        return false;
    }
 
    std::set<int> nodi(cycle.begin(), cycle.end());
    if (nodi.size() != cycle.size()) {
        return false;   // repeated node
    }
 
    const int L = static_cast<int>(cycle.size());
    for (int s = 0; s < L; s++) {
        int u = cycle[s];
        int v = cycle[(s + 1) % L];
        if (G.edge_number(edge<int>(u, v)) == -1) {
            return false;
        }
    }
    return true;
}
 
// 1) A tree must have no cycles
static int test_cicli_dfs_albero()
{
    auto cicli = cicli_DFS(F_albero);
    if (!cicli.empty()) {
        std::cerr << "ERROR: test_cicli_dfs_albero: expected 0 cycles, found "
                   << cicli.size() << "\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_cicli_dfs_albero\n";
    return EXIT_SUCCESS;
}
 
// 2) Correct number of cycles on a graph with cycles
static int test_cicli_dfs_numero()
{
    auto cicli = cicli_DFS(G_ciclico);
    const int n = static_cast<int>(G_ciclico.all_nodes().size());
    const int m = static_cast<int>(G_ciclico.all_edges().size());
    const int attesi = m - n + 1;
 
    if (static_cast<int>(cicli.size()) != attesi) {
        std::cerr << "ERROR: test_cicli_dfs_numero: expected " << attesi
                   << " cycles, found " << cicli.size() << "\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_cicli_dfs_numero\n";
    return EXIT_SUCCESS;
}
 
// 3) Each returned cycle must actually be a valid cycle of the graph
static int test_cicli_dfs_validita()
{
    auto cicli = cicli_DFS(G_ciclico);
 
    for (std::size_t i = 0; i < cicli.size(); i++) {
        if (!is_ciclo_valido(G_ciclico, cicli[i])) {
            std::cerr << "ERROR: test_cicli_dfs_validita: cycle " << i << " invalid\n";
            return EXIT_FAILURE;
        }
    }
    std::cout << "[OK] test_cicli_dfs_validita\n";
    return EXIT_SUCCESS;
}
 
// 4) The cycles must be independent
static int test_cicli_dfs_indipendenza()
{
    auto cicli = cicli_DFS(G_ciclico);
    std::set<edge<int>> archi_visti;
 
    for (const auto& cycle : cicli) {
        const int L = static_cast<int>(cycle.size());
        bool ha_arco_nuovo = false;
        for (int s = 0; s < L; s++) {
            edge<int> e(cycle[s], cycle[(s + 1) % L]);
            if (archi_visti.insert(e).second) {
                ha_arco_nuovo = true;
            }
        }
        if (!ha_arco_nuovo) {
            std::cerr << "ERROR: test_cicli_dfs_indipendenza: cycle without a new edge\n";
            return EXIT_FAILURE;
        }
    }
    std::cout << "[OK] test_cicli_dfs_indipendenza\n";
    return EXIT_SUCCESS;
}
 
int main()
{
    F_albero.add_edge(edge<int>(0, 1));
    F_albero.add_edge(edge<int>(1, 2));
    F_albero.add_edge(edge<int>(2, 3));
 
    G_ciclico.add_edge(edge<int>(0, 1));
    G_ciclico.add_edge(edge<int>(1, 2));
    G_ciclico.add_edge(edge<int>(2, 3));
    G_ciclico.add_edge(edge<int>(3, 0));
    G_ciclico.add_edge(edge<int>(0, 2));
 
    int falliti = 0;
    falliti += test_cicli_dfs_albero()       == EXIT_SUCCESS ? 0 : 1;
    falliti += test_cicli_dfs_numero()       == EXIT_SUCCESS ? 0 : 1;
    falliti += test_cicli_dfs_validita()     == EXIT_SUCCESS ? 0 : 1;
    falliti += test_cicli_dfs_indipendenza() == EXIT_SUCCESS ? 0 : 1;
 
    if (falliti == 0) {
        std::cout << "\nAll the cycles DFS tests have passed.\n";
        return EXIT_SUCCESS;
    } else {
        std::cerr << "\n" << falliti << " failed test.\n";
        return EXIT_FAILURE;
    }
}