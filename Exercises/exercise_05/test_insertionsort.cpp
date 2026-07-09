#include <iostream>		//stampa
#include <vector>
#include <string>
#include <cstdlib>
#include "sort.hpp"
#include "randfiller.h"

int main() 
{ 
	srand(time(NULL));			//per inizializzare il generatore di numeri casuali 
	randfiller rf; /* instantiate a randfiller */ 
	
	std::vector<int> dim(100); 		//vettore delle dimensioni
	rf.fill(dim, 0, 1000);		//riempio il vettore di dimensioni casuali da 0 a 1000
	
	std::vector<int> vec; 		//creo un unico vettore che ogni volta ridimensionerò, riempirò e testerò 
	for (int i=0; i < 100; i++) {
		vec.resize(dim[i]);
		rf.fill(vec, -10000, 10000);
		insertionsort(vec);
		
		if (! is_sorted(vec) ) {
			std::cerr << "Fallimento: vettore di dimensione "<< dim[i] << " non è ordinato\n";
			return EXIT_FAILURE;
		}
	}
	
	/* TEST SU STRINGHE */
	std::vector<std::string> costellazioni = {"Orion", "Lyra", "lyra", "", "Cassiopeia", "Andromeda", "Cygnus", "Draco", "Pegasus", "Scorpius", "UrsaMajor", "Aquarius"};
	insertionsort(costellazioni);
	if (! is_sorted(costellazioni) ) {
			std::cerr << "Errore nell'ordinamento di un vettore di stringhe (costellazioni)\n";
			return EXIT_FAILURE;
		}
	
	std::vector<std::string> lettere = {"Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta", "Eta", "Theta", "Lambda", "Omega"};
	insertionsort(lettere);
	if (! is_sorted(lettere) ) {
			std::cerr << "Errore nell'ordinamento di un vettore di stringhe (lettere)\n";
			return EXIT_FAILURE;
		}
	
	std::vector<std::string> citta = {"Tokyo", "Paris", "NewYork", "Sydney", "Cairo", "Berlin", "Toronto", "Dubai", "Rome", "Barcelona"};
	insertionsort(citta);
	if (! is_sorted(citta) ) {
			std::cerr << "Errore nell'ordinamento di un vettore di stringhe (città)\n";
			return EXIT_FAILURE;
		}
	
	
	std::cout << "Successo: i test su tutti i vettori sono stati superati con successo";
	return EXIT_SUCCESS;
}
