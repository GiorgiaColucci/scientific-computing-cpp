#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype> //for toupper

#include "lifo.hpp"
#include "graph_visit.hpp"
#include "netlist_struct.hpp"
#include "graph_construction.hpp"
#include "cycles_DFS.hpp"
#include "de_pina.hpp"
#include "solve.hpp"
#include "print_graphs.hpp"

// Print usage message
void stampa_uso (const char* nome_prog)
{
    std::cout << "Uso: "<< nome_prog << " <path/della/netlist> \n"
              << "ESEMPIO:  " << nome_prog << " netlists/esempio_traccia.txt \n";
}

int main(int argc, char* argv[])
{
    // there must be exactly one path
    if (argc<2) {
        std::cerr << "ERRORE: numero di argomenti errato\n";
        stampa_uso(argv[0]);
        return EXIT_FAILURE;
    }

	bool usa_dfs = false; // De Pina by default
	std::string scelta;
    
	while(true) {
		std::cout << "Scegliere l'algoritmo per il calcolo dei cicli: \n"
				  << "[1] per  De Pina (cicli minimi) \n"
				  << "[2] per DFS \n";
		std::cin >> scelta;
		if (scelta == "2") {
			usa_dfs = true;
			break;
		}
		else if (scelta == "1") {
			break;
		}
		else {
			std::cout << "Scelta non valida! Per favore, inserisci 1 o 2.\n\n";
		}
	}

    const std::string path_netlist = argv[1];
    Output result = parse_netlist(path_netlist);

    if (result.ok == false) {
        return EXIT_FAILURE;
    }

    if (result.componenti.empty()) {
        std::cerr << "ERRORE: la netlist " << path_netlist 
                  << " non contiene componenti\n";
        return EXIT_FAILURE;
    }

    // BUuld the graph and the auxiliary maps 
    std::map<edge<int>, edge_data> edge_data_map;

    graph<int> G = costruisci_grafo(result, edge_data_map);
    
    int nodo_radice = G.edge_at(0).from();
    lifo<int> stack;
    graph<int> T_graph = graph_visit(G, nodo_radice, stack);
    graph<int> C_graph = G - T_graph;

    // check that the graph is connected
    if (T_graph.all_nodes().size() != G.all_nodes().size()) {
	std::cerr << "ERRORE: il grafo del circuito non è connesso\n";
    	return EXIT_FAILURE;
    }

    // Circuito summary
    const int n_nodi        = static_cast<int>(G.all_nodes().size());
    const int n_componenti  = static_cast<int>(G.all_edges().size());
    const int n_maglie      = n_componenti - n_nodi + 1;

    std::cout   <<"\n" << "Netlist:    " << path_netlist   << "\n"
                << "Nodi:       " << n_nodi         << "\n"
                << "Componenti: " << n_componenti   << "\n"
                << "Maglie:     " << n_maglie       << "\n"
                << "Metodo:     " << (usa_dfs ? "DFS" : "De Pina") << "\n";

    if (n_maglie <= 0) {
        std::cerr << "ERRORE: il grafo del circuito non ha cicli\n";
        return EXIT_FAILURE; 
    }

    std::vector<std::vector<int>> cicli;
    if (usa_dfs) {
        cicli = cicli_DFS(G);
    } else {
        cicli = De_Pina(G);
    }

    if (cicli.empty()) {
        std::cerr << "ERRORE: nessun ciclo trovato. \n";
        return EXIT_FAILURE;
    }

    RisultatoCircuit r = circuit(G, edge_data_map, cicli);
    if (r.nomi_resistori.empty()) {
	return EXIT_FAILURE;
    }

    stampa_risultati(r);

    bool stampa = false; // Si di default
	std::string scelta_stampa;

    while(true) {
		std::cout << "\nVuoi stampare i grafi? \n"
				  << "[Y] per si \n"
				  << "[N] per no \n";
		std::cin >> scelta_stampa;
		for (char& c : scelta_stampa) {
      			c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		}
		if (scelta_stampa == "Y") {
			stampa = true;
			break;
		}
		else if (scelta_stampa == "N") {
			break;
		}
		else {
			std::cout << "Scelta non valida! Per favore, inserisci Y o N.\n\n";
		}
	}

    // To get the graph images with GraphViz, the graphs must be translated into 
    // the DOT language (abstract grammar for defining Graphviz nodes, edges, graphs,
    //  subgraphs, and clusters)
    if (stampa) {          // or ask the user before returning
        const std::string grafo_dot = "grafo_principale.dot";
        const std::string grafo_png = "grafo.png";
        const std::string coalb_dot = "coalbero.dot";
        const std::string coalb_png = "coalbero.png";
        
        to_dot(G,        grafo_dot, edge_data_map);
        to_dot(C_graph,  coalb_dot, edge_data_map); 

        std::cout << "Grafo del circuito esportato in \"" << grafo_dot << "\".\n"
              << "Per generare l'immagine usa il comando:\n"
              << "  dot -Tpng " << grafo_dot << " -o " << grafo_png << "\n\n";

        std::cout << "Coalbero del circuito esportato in \"" << coalb_dot << "\".\n"
              << "Per generare l'immagine usa il comando:\n"
              << "  dot -Tpng " << coalb_dot << " -o " << coalb_png << "\n\n";
    }

    return EXIT_SUCCESS; 
}