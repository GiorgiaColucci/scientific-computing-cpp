#include "unidirected_graph.hpp"
#include <iostream>
#include <cstdlib> 	//per i risultati del test

/* Funzione di stampa dell'esito del test e aggiornamento il flag globale di fallimento */
void esito(const std::string& nome, bool ok, bool& tutti_ok) {
    std::cout << nome << ": " << (ok ? "successo" : "FALLIMENTO") << "\n\n";
    if (!ok) { tutti_ok = false; }
}
	
//faccio questa funzione esito con poi i booleani in modo che se si ferma a uno dei test intermedi non smette di andare avanti ma continua con gli altri test e poi solo alla fine mi dice ciò che era fallito
 
int main() {
	bool tutti_ok = true;
 
    /*  Test 1: costruzione e stampa */
    //Sto anche testando il costuttore di unidirected_edge; operatore di comparazione e di uguaglianza vengono usati dalla struttura di set, quindi se funziona tutto il resto, è ok
    std::cout << " Test 1: costruzione e stampa \n";
 
    unidirected_graph<int> g;
    g.add_edge(1, 2);
    g.add_edge(3, 1);   // verrà salvato come (1,3)
    g.add_edge(2, 3);
    g.add_edge(2, 3);   // duplicato: non deve essere inserito
 	
 	std::cout << g << "\n";
    // atteso: Nodi: { 1 2 3 }, Archi: { (1,2) (1,3) (2,3) }
    
 	unidirected_edge<int> check(3,1); 
    bool ok1 = (g.all_edges().size() == 3) 
    		&& (g.all_nodes().size() == 3)
    		&& check.from() == 1 && check.to() == 3
    		&& g.all_edges().count(check);	//l'arco c'è effettivamente dentro
    esito("Test 1, costruzione e stampa", ok1, tutti_ok);
    
    
    /*  Test 2: costruttore di copia e add_edge */
    std::cout << " Test 2: costruttore di copia \n";
 
    unidirected_graph<int> g_copy(g);
    g_copy.add_edge(4, 5);   // modifica solo la copia
    
    std::cout << "Originale (" << g.all_edges().size() << " archi):\n" << g << "\n";
    std::cout << "Copia     (" << g_copy.all_edges().size() << " archi):\n" << g_copy << "\n";
    
    bool ok2 = (g.all_edges().size() == 3) && (g_copy.all_edges().size() == 4); 
    esito("Test 2, costruttore di copia", ok2, tutti_ok); 
 
 
    /*  Test 3: neighbours  */
    std::cout << " Test 3: neighbours \n";
 
    auto vicini = g.neighbours(1);
    if (vicini.has_value()) {
        std::cout << "Vicini di 1: { ";
        for (const auto& n : vicini.value()) { std::cout << n << " "; }
        std::cout << "}\n";   // atteso: { 2 3 }
    }
    else {
	    std::cout << "Nodo non trovato (nullopt)\n";
    }
 
 	auto vicini_missing = g.neighbours(99);
    if (!vicini_missing.has_value()) {
        std::cout << "Nodo 99 non trovato (nullopt)\n";
    }
 
 	bool ok3 = vicini.has_value()
            && vicini.value().count(2)
            && vicini.value().count(3)
            && vicini.value().size() == 2
            && !vicini_missing.has_value();
    esito("Test 3, neighbours", ok3, tutti_ok);
    
 
 	/*  Test 4: all_edges e all_nodes */
    std::cout << " Test 4: all_edges e all_nodes \n";
 
    unidirected_edge<int> e12(1, 2);
    unidirected_edge<int> e13(1, 3);
    unidirected_edge<int> e23(2, 3);
    
	std::cout << "Tutti i nodi di g: { ";
    for (const auto& n : g.all_nodes()) { std::cout << n << " "; }
    std::cout << "}\n";   // atteso: { 1 2 3 }
 
    std::cout << "Tutti gli archi di g: { ";
    for (const auto& e : g.all_edges()) { std::cout << e << " "; }
    std::cout << "}\n";   // atteso: { (1,2) (1,3) (2,3) }
    
    bool ok4 = (g.all_nodes().size() == 3)
            && (g.all_edges().size() == 3)
            && g.all_nodes().count(1) && g.all_nodes().count(2) && g.all_nodes().count(3)
            && g.all_edges().count(e12) && g.all_edges().count(e13) && g.all_edges().count(e23);
    esito("Test 4, all_edges e all_nodes", ok4, tutti_ok);


    /*  Test 5: edge_number e edge_at */
    std::cout << " Test 5: edge_number e edge_at \n";
 
    auto num = g.edge_number(e12);
    if (num.has_value()) {
        std::cout << "Numero di (1,2): " << num.value() << "\n";  // atteso: 0
    }
 
    auto arco = g.edge_at(2);
    if (arco.has_value()) {
        std::cout << "Arco in posizione 2: " << arco.value() << "\n";  // atteso: (2,3)
    }
 	
 	auto n_miss = g.edge_number(unidirected_edge<int>(9, 10));
 	if (!n_miss.has_value()) {
	 	std::cout << "Arco (9,10) non presente (nullopt)\n";
	}
 	
    auto out = g.edge_at(10);
    if (!out.has_value()) {
        std::cout << "Indice 10 fuori range (nullopt)\n";
    }
 
 	bool ok5 = num.has_value()   && num.value()  == 0
            && arco.has_value()  && arco.value() == e23
            && !out.has_value()
            && !n_miss.has_value();
    esito("Test 5, edge_number e edge_at", ok5, tutti_ok);
 
  	 
    /*  Test 6: differenza tra grafi */
    std::cout << " Test 6: differenza G - G' \n";
 
    unidirected_graph<int> g2;
    g2.add_edge(1, 2);   // arco in comune con g
 
    unidirected_graph<int> diff = g - g2;

    std::cout << "G - G':\n" << diff << "\n";
    // atteso: archi (1,3) e (2,3), non (1,2)
    
    bool ok6 = (diff.all_edges().size() == 2)
            && diff.all_edges().count(e13)
            && diff.all_edges().count(e23)
            && !diff.all_edges().count(e12);
    esito("Test 6, differenza G - G'", ok6, tutti_ok);
    
    
    /*  Esito finale */
    std::cout << "-----------------------------------\n";
    if (tutti_ok) {
        std::cout << "Tutti i test superati.\n";
        return EXIT_SUCCESS;
    } else {
        std::cout << "Uno o piu' test falliti.\n";
        return EXIT_FAILURE;
    }

}
