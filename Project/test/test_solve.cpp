#include "netlist_struct.hpp"
#include "graph_construction.hpp"
#include "cycles_DFS.hpp"
#include "de_pina.hpp"
#include "solve.hpp"

#include <map>
#include <cstdlib>
#include <iostream>
#include <cmath>

/* The test
    1) Read the netlist from 'sample.txt'
    2) Builds the graph
    3) Compute the cycles
    4) Solves the system
    5) Checks that voltages and currents match the expexted values
    
     R1: V =  8 volts, I =  2.0 amps
     R2: V = 22 volts, I =  2.2 amps
     R3: V = -6 volts, I = -0.2 amps
     R4: V = -28 volts, I = -2.8 amps
     R5: V = 12 volts, I =  3.0 amps
*/

static const std::string NETLIST = "sample.txt";

// Read the netlist and declare the global graph + map variables; 
// initialize later in main()
Output dati;
std::map<edge<int>, edge_data> edge_data_map;

graph<int> G;
static const double tol = 1e-7;

struct Riferimento {
    double tensione;
    double corrente;
};

static const std::map<std::string, Riferimento> RIFERIMENTO = {
    {"R1", { 8.0,  2.0}},
    {"R2", {22.0,  2.2}},
    {"R3", {-6.0, -0.2}},
    {"R4", {-28.0,-2.8}},
    {"R5", {12.0,  3.0}},
};

// Compare the solver result with the reference values, indexing / by resistor name
static bool risultati_corretti(const RisultatoCircuit& r, const std::string& nome_test)
{
    if (r.nomi_resistori.size() != RIFERIMENTO.size()) {
        std::cerr << "ERROR: " << nome_test << ": expected " << RIFERIMENTO.size()
                   << " resistor, found " << r.nomi_resistori.size() << "\n";
        return false;
    }

    bool ok = true;
    for (std::size_t i = 0; i < r.nomi_resistori.size(); i++) {
        const std::string& nome = r.nomi_resistori[i];
        auto it = RIFERIMENTO.find(nome);
        if (it == RIFERIMENTO.end()) {
            std::cerr << "ERROR: " << nome_test << ": unknown resistor \"" << nome << "\"\n";
            ok = false;
            continue;
        }
        if (std::abs(r.tensioni[i] - it->second.tensione) > tol) {
            std::cerr << "ERROR: " << nome_test << ": " << nome
                       << ": V = " << r.tensioni[i] << ", expected " << it->second.tensione << "\n";
            ok = false;
        }
        if (std::abs(r.correnti[i] - it->second.corrente) > tol) {
            std::cerr << "ERROE: " << nome_test << ": " << nome
                       << ": I = " << r.correnti[i] << ", expected " << it->second.corrente << "\n";
            ok = false;
        }
    }
    return ok;
}

// 1) Solve using fundamental cycles (DFS + cotree)
static int test_solve_dfs()
{
    auto cicli = cicli_DFS(G);
    RisultatoCircuit r = circuit(G, edge_data_map, cicli);

    if (!risultati_corretti(r, "test_solve_dfs")) {
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_solve_dfs\n";
    return EXIT_SUCCESS;
}

// 2) Solve using minimum cycles (De Pina)
static int test_solve_depina()
{
    auto cicli = De_Pina(G);
    RisultatoCircuit r = circuit(G, edge_data_map, cicli);

    if (!risultati_corretti(r, "test_solve_depina")) {
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_solve_depina\n";
    return EXIT_SUCCESS;
}

int main()
{
    // If the file is not found we exit immediately, without crashing inside the test functions
    dati = parse_netlist(NETLIST);
    if (!dati.ok) {
        std::cerr << "ERROR: cannot read the netlist\n";
        return EXIT_FAILURE;
    }

    G = costruisci_grafo(dati, edge_data_map);

    int falliti = 0;
    falliti += test_solve_dfs()    == EXIT_SUCCESS ? 0 : 1;
    falliti += test_solve_depina() == EXIT_SUCCESS ? 0 : 1;

    if (falliti == 0) {
        std::cout << "\nAll the solver tests have passed.\n";
        return EXIT_SUCCESS;
    } else {
        std::cerr << "\n" << falliti << " failed tests.\n";
        return EXIT_FAILURE;
    }
}
