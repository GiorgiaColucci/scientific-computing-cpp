#include <iostream>
#include <vector>
#include "graph.hpp"
#include "edge.hpp"
#include "print_graphs.hpp"
#include "de_pina.hpp"
#include "test_de_pina_helper.hpp"

/* Unit tests for the De Pina algorithm
	- Check that a tree has no cycles.
	- Check the minimum cycle for a graph that is a single cycle.
	- Check the minimum cycles for a simple graph with cycles.
*/

int main() {
	// build the edges
	edge<int> e_1(0,1);
	edge<int> e_2(1,2);
	edge<int> e_3(2,3);
	edge<int> e_4(3,0);
	edge<int> e_5(0,2);

	// initialize the graphs
	graph<int> F_de_pina_test; // tree (hence no cycles)
	graph<int> G_de_pina_test; // grpah with cycles
	graph<int> H_de_pina_test; // graph that is a single cycle 

	// fill the graphs
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

	// De Pina output and expected solutions
	std::vector<std::vector<int>> guess_F = De_Pina(F_de_pina_test);
	std::vector<std::vector<int>> solution_F = {};
	std::vector<std::vector<int>> guess_G = De_Pina(G_de_pina_test);
	std::vector<std::vector<int>> solution_G = {{0, 1, 2, 0}, {0, 2, 3, 0}};
	std::vector<std::vector<int>> guess_H = De_Pina(H_de_pina_test);
	std::vector<std::vector<int>> solution_H = {{0, 1, 2, 0}};
	

	// comparison and results
	int global_res = EXIT_SUCCESS;
	
	if (guess_F != solution_F) {
		global_res = EXIT_FAILURE;
		std::cout << "Test su albero fallito" << "\n";
	}
	else {
		std::cout << "Test su albero riuscito" << "\n";
	}

	// to make the comparison between guess and solution robust for graphs G 
	// and H, we normalize them with the helper functions normalize_cycle and 
	// normalize_basis (defined and explained in "test_de_pina_helper.hpp")

	// Note: this step could have been avoided by implementing De Pina so that it 
	// returned boolean vectors indicating which edges belong to each minimum cycle; 
	// however, returning node sequences was chosen to make later accesses easier

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