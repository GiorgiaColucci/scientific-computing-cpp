#include <iostream>
#include <vector>
#include "graph.hpp"
#include "edge.hpp"
#include "stampa_grafi.hpp"
#include "de_pina.hpp"
#include "test_de_pina_helper.hpp"
/*Test unitari per l'algoritmo di De Pina
	- Verifica di assenza di cicli in un albero.
	- Verifica di un ciclo minimo per un grafo che sia solo un ciclo.
	- Verifica di cicli minimi per un grafo con cicli semplice.
*/

int main() {
	//costruzione degli archi
	edge<int> e_1(0,1);
	edge<int> e_2(1,2);
	edge<int> e_3(2,3);
	edge<int> e_4(3,0);
	edge<int> e_5(0,2);

	//inizializzazione dei grafi
	graph<int> F_de_pina_test; //albero (quindi senza cicli)
	graph<int> G_de_pina_test; //grafo con cicli
	graph<int> H_de_pina_test; //grafo che sia solo un ciclo

	//riempimento dei grafi
	F_de_pina_test.add_edge(e_1);
	F_de_pina_test.add_edge(e_2);
	F_de_pina_test.add_edge(e_3);
	G_de_pina_test.add_edge(e_1);
	G_de_pina_test.add_edge(e_2);
	G_de_pina_test.add_edge(e_3);
	G_de_pina_test.add_edge(e_4);
	G_de_pina_test.add_edge(e_5);
	H_de_pina_test.add_edge(e_1);
	H_de_pina_test.add_edge(e_2);
	H_de_pina_test.add_edge(e_5);

	//output di De Pina e soluzioni
	std::vector<std::vector<int>> guess_F = De_Pina(F_de_pina_test);
	std::vector<std::vector<int>> solution_F = {};
	std::vector<std::vector<int>> guess_G = De_Pina(G_de_pina_test);
	std::vector<std::vector<int>> solution_G = {{0, 1, 2, 0}, {0, 2, 3, 0}};
	std::vector<std::vector<int>> guess_H = De_Pina(H_de_pina_test);
	std::vector<std::vector<int>> solution_H = {{0, 1, 2, 0}};
	

	//confronto e risultati
	int global_res = EXIT_SUCCESS;
	
	if (guess_F != solution_F) {
		global_res = EXIT_FAILURE;
		std::cout << "Test su albero fallito" << "\n";
	}
	else {
		std::cout << "Test su albero riuscito" << "\n";
	}

	//per rendere robusto il confronto tra guess e solution per i grafi G e H li normalizziamo con le funzioni helper normalize_cycle e normalize_basis (definite e spiegate in "test_de_pina_helper.hpp")
	//Nota: si sarebbe potuto evitare questo procedimento implementando De Pina in modo che restituisse dei vettori booleani su quali archi considerare in ogni ciclo minimo (come da pseudocodice nella relativa lezione), tuttavia è stato scelto di restituire le sequenze dei nodi per agevolare gli accessi successivi.

	if (normalize_basis(guess_G) != normalize_basis(solution_G)) {
		global_res = EXIT_FAILURE;
		std::cout << "Test su grafo con cicli fallito" << "\n";
	}
	else {
		std::cout << "Test su grafo con cicli riuscito" << "\n";
	}

	if (normalize_basis(guess_H) != normalize_basis(solution_H)) {
		global_res = EXIT_FAILURE;
		std::cout << "Test su grafo con un ciclo solo fallito" << "\n";
	}
	else {
		std::cout << "Test su grafo con un ciclo solo riuscito" << "\n";
	}

	return global_res;
}