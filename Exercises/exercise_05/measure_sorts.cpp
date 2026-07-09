#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

#include "timecounter.h"
#include "sort.hpp"
#include "randfiller.h"


int main(void)
{	std::vector<int> dim;			//vettore delle dimensioni
	for (int i = 2; i<= 100; i += 2) 	//uso dimensioni molto piccole e fitte, che mi permette di pesare meglio l'overhead di mergesort e quicksort, che è fisso (chiamate ricorsive, allocazionioni di memoria per sottovettori temporanei)
	{ dim.push_back(i); }
	
	/*per realizzare i vettori in Matlab mi serve un vettore per ciascun metodo contenente i tempi*/
	std::vector<double> y_bubble;
	std::vector<double> y_select;
	std::vector<double> y_insert;
	std::vector<double> y_merge;
	std::vector<double> y_quick;
	std::vector<double> y_std;
	
	randfiller rf(42); //creo randfiller e fisso il seed per confronto equo
	std::cout << "\n";
	std::vector<std::vector<int>> vecs;		//creo un vettore di vettori
	vecs.resize(100); 			//prealloco il vettore per evitare crash e non avere accessi fuori range
	
	for (int n=0; n < (int)dim.size(); n++) {
		
		for (int i=0; i < 100; i++) 		//metto 100 vettori della dimensione che voglio testare
		{
			vecs[i].resize(dim[n]);
			rf.fill(vecs[i], -100, 100);
		};
		
		timecounter tc; /* instantiate the timecounter */
		
		//creo le copie dei vettori da riordinare
		std::vector<std::vector<int>> v1 = vecs;		
		std::vector<std::vector<int>> v2 = vecs; 
		std::vector<std::vector<int>> v3 = vecs; 
		std::vector<std::vector<int>> v4 = vecs;
		std::vector<std::vector<int>> v5 = vecs;
		std::vector<std::vector<int>> v6 = vecs; 

		tc.tic();       /* start it */
		for (int v = 0; v < (int)v1.size(); v++) { bubblesort(v1[v]); }
		double secs_b = tc.toc();
		double secs_b_med = secs_b/100; 
		y_bubble.push_back(secs_b_med);
				
		tc.tic();       /* start it */
		for (int v = 0; v < (int)v2.size(); v++) { selectionsort(v2[v]); }
		double secs_s = tc.toc();
		double secs_s_med = secs_s/100;
		y_select.push_back(secs_s_med);
				
		tc.tic();       /* start it */
		for (int v = 0; v < (int)v3.size(); v++) { insertionsort(v3[v]); }
		double secs_i = tc.toc();
		double secs_i_med = secs_i/100;
		y_insert.push_back(secs_i_med);
		
		tc.tic();       /* start it */
		for (int v = 0; v < (int)v4.size(); v++) { mergesort(v4[v], 0, (int)v4[v].size()-1); }
		double secs_m = tc.toc();
		double secs_m_med = secs_m/100;
		y_merge.push_back(secs_m_med);	
		
		tc.tic();       /* start it */ 
		for (int v = 0; v < (int)v5.size(); v++) { quicksort(v5[v], 0, (int)v5[v].size()-1); }
		double secs_q = tc.toc();
		double secs_q_med = secs_q/100;
		y_quick.push_back(secs_q_med);
		
		tc.tic();       /* start it */
		for (int v = 0; v < (int)v6.size(); v++) { std::sort(v6[v].begin(), v6[v].end()); }
		double secs_std = tc.toc();
		double secs_std_med = secs_std/100;
		y_std.push_back(secs_std_med);
		
		/*Stampo i risultato ogni volta per vedere effettivamente le differenze nei 4 algoritmi*/
		std::cout << "Dimensione " << dim[n] << "\n";
		std::cout << "Bubble-sort elapsed time: " << secs_b_med << " seconds\n";
		std::cout << "Selection-sort elapsed time: " << secs_s_med << " seconds\n";
		std::cout << "Insertion-sort elapsed time: " << secs_i_med << " seconds\n";
		std::cout << "Merge-sort elapsed time: " << secs_m_med << " seconds\n";
		std::cout << "Quick-sort elapsed time: " << secs_q_med << " seconds\n";
		std::cout << "Standard sort elapsed time: " << secs_std_med << " seconds\n";
		std::cout << "\n";
	}	
	
	/* Usando la funzione template inclusa nel sort.hpp, stampo il vettore delle dimensioni da usare per i grafici (asse x) e i vettori dei tempi ottenuti con ciascun metodo (asse y).*/
	std::cout << "dim"; 
	print_vector(dim);
	std::cout << "\n";
	std::cout << "y_bubble"; 
	print_vector(y_bubble);
	std::cout << "\n";
	std::cout << "y_select"; 
	print_vector(y_select);
	std::cout << "\n";
	std::cout << "y_insert"; 
	print_vector(y_insert);
	std::cout << "\n";
	std::cout << "y_merge";
	print_vector(y_merge);
	std::cout << "\n";
	std::cout << "y_quick";
	print_vector(y_quick);
	std::cout << "\n";
	std::cout << "y_std";
	print_vector(y_std);
	
	return 0;
}
