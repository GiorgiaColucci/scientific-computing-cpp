#include "netlist_struct.hpp"
#include "graph_construction.hpp"

#include <cstdlib>
#include <iostream>
#include <map>
#include <cmath>

/* Unit tests for graph construction from the netlist 'sample.txt'
   (5 nodes, 7 components)

   The test:
     1) reads sample.txt with parse_netlist
     2) builds the graph with the graph-construction function
     3) checks nodes and edges
*/

static const std::string NETLIST= "sample.txt";

// Read the netlist and declare the global graph + map variables; initialize 
// later in main(); (the test functions are static and access them directly)
Output dati;

std::map<edge<int>, edge_data> edge_data_map;

graph<int> G;
static const double tol = 1e-7;

// 1. Number of nodes and edges
static int test_grafo_dim() 
{
    if (!dati.ok) {
        std::cerr << "ERRORE: parsing della netlist fallito\n";
        return EXIT_FAILURE;
    }
    if (G.all_nodes().size() != 5) {
        std::cerr << "ERRORE: test_grafo_dim: attesi 5 nodi\n";
        return EXIT_FAILURE;
    }
    if (G.all_edges().size() != 7) {
        std::cerr << "ERRORE: test_grafo_dim: attesi 7 archi\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_grafo_dim\n";
    return EXIT_SUCCESS;
}

// 2. Type: R1 on (2,4), V1 on (1,4), V2 on (3,5) 
static int test_grafo_tipologia()
{
    if (edge_data_map.at(edge<int>(2,4)).tipologia != TipoComponente::Resistore) {
        std::cerr << "ERRORE: test_grafo_tipologia: (2,4) doveva essere Resistore\n";
        return EXIT_FAILURE;
    }

    if (edge_data_map.at(edge<int>(1,4)).tipologia != TipoComponente::Generatore) {
        std::cerr << "ERRORE: test_grafo_tipologia: (1,4) doveva essere Generatore\n";
        return EXIT_FAILURE;
    }

    if (edge_data_map.at(edge<int>(3,5)).tipologia != TipoComponente::Generatore) {
        std::cerr << "ERRORE: test_grafo_tipologia: (3,5) doveva essere Generatore\n";
        return EXIT_FAILURE;
    }

    std::cout << "[OK] test_grafo_tipologia\n";
    return EXIT_SUCCESS;
}

// 3. Values
static int test_grafo_valori()
{
    if (std::abs(edge_data_map.at(edge<int>(2,4)).valori - 4.0)  > tol ||  
        std::abs(edge_data_map.at(edge<int>(1,2)).valori - 10.0) > tol ||  
        std::abs(edge_data_map.at(edge<int>(1,3)).valori - 30.0) > tol ||  
        std::abs(edge_data_map.at(edge<int>(1,4)).valori - 30.0) > tol) {  
        std::cerr << "ERRORE: test_grafo_valori\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_grafo_valori\n";
    return EXIT_SUCCESS;
}

// 4. Positive direction 
static int test_grafo_verso_positivo()
{
    if (!edge_data_map.at(edge<int>(1,4)).verso_positivo) {
        std::cerr << "ERRORE: test_grafo_verso_positivo: V1 (1->4) deve essere true\n";
        return EXIT_FAILURE;
    }
    if (edge_data_map.at(edge<int>(2,4)).verso_positivo) {
        std::cerr << "ERRORE: test_grafo_verso_positivo: R1 (4->2) deve essere false\n";
        return EXIT_FAILURE;
    }
    if (!edge_data_map.at(edge<int>(1,2)).verso_positivo) {
        std::cerr << "ERRORE: test_grafo_verso_positivo: R2 (1->2) deve essere true\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_grafo_verso_positivo\n";
    return EXIT_SUCCESS;
}

// 5. Names
static int test_grafo_nomi()
{
    if (edge_data_map.at(edge<int>(2,4)).nome != "R1" ||
        edge_data_map.at(edge<int>(1,2)).nome != "R2" ||
        edge_data_map.at(edge<int>(1,4)).nome != "V1" ||
        edge_data_map.at(edge<int>(3,5)).nome != "V2") {
        std::cerr << "ERRORE: test_grafo_nomi\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_grafo_nomi\n";
    return EXIT_SUCCESS;
}

 
int main()
{
    // Initialize here: if the file is not found we exit immediately, 
    // without crashing inside the test functions
    dati = parse_netlist(NETLIST);
    if (!dati.ok) {
        std::cerr << "ERRORE: impossibile leggere la netlist\n";
        return EXIT_FAILURE;
    }

    G = costruisci_grafo(dati, edge_data_map);

    int falliti = 0;
    falliti += test_grafo_dim()             == EXIT_SUCCESS ? 0 : 1;
    falliti += test_grafo_tipologia()       == EXIT_SUCCESS ? 0 : 1;
    falliti += test_grafo_valori()          == EXIT_SUCCESS ? 0 : 1;
    falliti += test_grafo_nomi()            == EXIT_SUCCESS ? 0 : 1;
    falliti += test_grafo_verso_positivo()  == EXIT_SUCCESS ? 0 : 1;
 
    if (falliti == 0) {
        std::cout << "\nTutti i test del grafo sono passati.\n";
        return EXIT_SUCCESS;
    } else {
        std::cerr << "\n" << falliti << " test falliti.\n";
        return EXIT_FAILURE;
    }
}