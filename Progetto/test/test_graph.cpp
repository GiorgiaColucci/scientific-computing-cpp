#include "netlist_struct.hpp"
#include "graph_construction.hpp"

#include <cstdlib>
#include <iostream>
#include <map>
#include <cmath>

/* Test unitari per costruisci_grafo a partire dalla netlist 'sample.txt'
   (5 nodi, 7 componenti)
  
   Il test:
     1) legge sample.txt con parse_netlist
     2) costruisce il grafo con costruisci_grafo
     3) verifica nodi, archi
*/
 

static const std::string NETLIST= "sample.txt";

// Leggo netlist e dichiaro le variabili globali di grafo + mappa; inizializzo 
// poi in main(); (le funzioni di test sono static e le accedono direttamente)
Output dati;

std::map<edge<int>, edge_data> edge_data_map;

graph<int> G;
static const double tol = 1e-7;

// 1. Numero nodi e archi
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

// 2. Tipologia: R1 su (2,4), V1 su (1,4), V2 su (3,5) 
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

// 3. Valori
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

// 4. Verso Positivo 
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

// 5. Nomi
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
    // Inizializzazione qui: se il file non si trova si esce subito, senza
    // crashare dentro le funzioni di test
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