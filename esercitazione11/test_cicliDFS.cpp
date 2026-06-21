#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"
#include "cicli.hpp"
 
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
 
/* Test unitari per cicli_DFS (cicli fondamentali via DFS + coalbero).
 
   Usiamo gli stessi grafi di test_de_pina.cpp, per poter
   confrontare a occhio i due algoritmi sullo stesso input:
     - F_albero:  4 nodi, 3 archi - un albero, nessun ciclo
     - G_ciclico: F_albero + 2 archi - 2 cicli fondamentali (= archi - nodi + 1)
*/
 
unidirected_graph<int> F_albero;
unidirected_graph<int> G_ciclico;
 
// Verifica che 'cycle' sia un ciclo valido in G: nodi tutti distinti e ogni
// coppia consecutiva e' un arco di G.
static bool is_ciclo_valido(const unidirected_graph<int>& G, const std::vector<int>& cycle)
{
    if (cycle.size() < 3) {
        return false;
    }
 
    std::set<int> nodi(cycle.begin(), cycle.end());
    if (nodi.size() != cycle.size()) {
        return false;   // nodo ripetuto
    }
 
    const int L = static_cast<int>(cycle.size());
    for (int s = 0; s < L; s++) {
        int u = cycle[s];
        int v = cycle[(s + 1) % L];
        if (!G.edge_number(unidirected_edge<int>(u, v)).has_value()) {
            return false;
        }
    }
    return true;
}
 
// 1) Su un albero non devono esserci cicli
static int test_cicli_dfs_albero()
{
    auto cicli = cicli_DFS(F_albero);
    if (!cicli.empty()) {
        std::cerr << "ERRORE: test_cicli_dfs_albero: attesi 0 cicli, trovati "
                   << cicli.size() << "\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_cicli_dfs_albero\n";
    return EXIT_SUCCESS;
}
 
// 2) Numero di cicli corretto su un grafo con cicli
static int test_cicli_dfs_numero()
{
    auto cicli = cicli_DFS(G_ciclico);
    const int n = static_cast<int>(G_ciclico.all_nodes().size());
    const int m = static_cast<int>(G_ciclico.all_edges().size());
    const int attesi = m - n + 1;
 
    if (static_cast<int>(cicli.size()) != attesi) {
        std::cerr << "ERRORE: test_cicli_dfs_numero: attesi " << attesi
                   << " cicli, trovati " << cicli.size() << "\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_cicli_dfs_numero\n";
    return EXIT_SUCCESS;
}
 
// 3) Ogni ciclo restituito deve essere effettivamente un ciclo valido del grafo
static int test_cicli_dfs_validita()
{
    auto cicli = cicli_DFS(G_ciclico);
 
    for (std::size_t i = 0; i < cicli.size(); i++) {
        if (!is_ciclo_valido(G_ciclico, cicli[i])) {
            std::cerr << "ERRORE: test_cicli_dfs_validita: ciclo " << i << " non valido\n";
            return EXIT_FAILURE;
        }
    }
    std::cout << "[OK] test_cicli_dfs_validita\n";
    return EXIT_SUCCESS;
}
 
// 4) I cicli devono essere indipendenti
static int test_cicli_dfs_indipendenza()
{
    auto cicli = cicli_DFS(G_ciclico);
    std::set<unidirected_edge<int>> archi_visti;
 
    for (const auto& cycle : cicli) {
        const int L = static_cast<int>(cycle.size());
        bool ha_arco_nuovo = false;
        for (int s = 0; s < L; s++) {
            unidirected_edge<int> e(cycle[s], cycle[(s + 1) % L]);
            if (archi_visti.insert(e).second) {
                ha_arco_nuovo = true;
            }
        }
        if (!ha_arco_nuovo) {
            std::cerr << "ERRORE: test_cicli_dfs_indipendenza: ciclo senza arco nuovo\n";
            return EXIT_FAILURE;
        }
    }
    std::cout << "[OK] test_cicli_dfs_indipendenza\n";
    return EXIT_SUCCESS;
}
 
int main()
{
    F_albero.add_edge(0, 1);
    F_albero.add_edge(1, 2);
    F_albero.add_edge(2, 3);
 
    G_ciclico.add_edge(0, 1);
    G_ciclico.add_edge(1, 2);
    G_ciclico.add_edge(2, 3);
    G_ciclico.add_edge(3, 0);
    G_ciclico.add_edge(0, 2);
 
    int falliti = 0;
    falliti += test_cicli_dfs_albero()       == EXIT_SUCCESS ? 0 : 1;
    falliti += test_cicli_dfs_numero()       == EXIT_SUCCESS ? 0 : 1;
    falliti += test_cicli_dfs_validita()     == EXIT_SUCCESS ? 0 : 1;
    falliti += test_cicli_dfs_indipendenza() == EXIT_SUCCESS ? 0 : 1;
 
    if (falliti == 0) {
        std::cout << "\nTutti i test sui cicli DFS sono passati.\n";
        return EXIT_SUCCESS;
    } else {
        std::cerr << "\n" << falliti << " test falliti.\n";
        return EXIT_FAILURE;
    }
}