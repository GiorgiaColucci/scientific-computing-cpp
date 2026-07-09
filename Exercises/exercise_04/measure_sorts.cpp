#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

#include "timecounter.h"
#include "sort.hpp"
#include "randfiller.h"


int main(void)
{
	std::vector<int> dim;			//vettore delle dimensioni
	for (int i = 4; i<= 1982; i *= 2) {
		dim.push_back(i);
	}
	
	/*per realizzare i vettori in Matlab mi serve un vettore per ciascun metodo contenente i tempi*/
	std::vector<double> y_bubble;
	std::vector<double> y_select;
	std::vector<double> y_insert;
	std::vector<double> y_std;
	
	std::vector<int> vec; 		//creo un unico vettore che ogni volta ridimensionerò, riempirò e userò per calcolare i tempi 
	randfiller rf(42); //creo randfiller e fisso il seed per confronto equo
	std::cout << "\n";
	for (int i=0; i < (int)dim.size(); i++) {
		vec.resize(dim[i]);
		rf.fill(vec, -100, 100);
		
		timecounter tc; /* instantiate the timecounter */
		
		//creo le copie dei vettori da riordinare
		std::vector<int> v1 = vec; 
		std::vector<int> v2 = vec; 
		std::vector<int> v3 = vec; 
		std::vector<int> v4 = vec; 

		tc.tic();       /* start it */
		bubblesort(v1);
		double secs_b = tc.toc();
		y_bubble.push_back(secs_b);
				
		tc.tic();       /* start it */
		selectionsort(v2);
		double secs_s = tc.toc();
		y_select.push_back(secs_s);
				
		tc.tic();       /* start it */
		insertionsort(v3);
		double secs_i = tc.toc();
		y_insert.push_back(secs_i);
		
		tc.tic();       /* start it */
		std::sort(v4.begin(), v4.end());
		double secs_std = tc.toc();
		y_std.push_back(secs_std);
		
		/*Stampo i risultato ogni volta per vedere effettivamente le differenze nei 4 algoritmi*/
		std::cout << "Dimensione " << dim[i] << "\n";
		std::cout << "Bubble-sort elapsed time: " << secs_b << " seconds\n";
		std::cout << "Selection-sort elapsed time: " << secs_s << " seconds\n";
		std::cout << "Insertion-sort elapsed time: " << secs_i << " seconds\n";
		std::cout << "Standard sort eElapsed time: " << secs_std << " seconds\n";
		std::cout << "\n";

	}	
	
	/* Usando la funzione template inclusa nel sort.hpp, stampo il vettore delle dimensioni da usare per i grafici (asse x) e i vettori dei tempi ottenuti con ciascun metodo (asse y).*/
	std::cout << "dim"; 
	print_vector(dim);
	std::cout << "y_bubble"; 
	print_vector(y_bubble);
	std::cout << "y_select"; 
	print_vector(y_select);
	std::cout << "y_insert"; 
	print_vector(y_insert);
	std::cout << "y_std";
	print_vector(y_std);
	
	return 0;
}
