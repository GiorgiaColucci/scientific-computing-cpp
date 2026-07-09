#pragma once 
#include <vector>
#include <algorithm>	//per swap
#include <cmath>		//per floor

template<typename T>
bool is_sorted(const std::vector<T>& vec)
{	//if (vec.size() == 0) { return true; }

	// controllo che sia da più piccolo a più grande 
	for (size_t i = 1; i < vec.size(); i++) 	//uso size_t : unsigned. (vec.size() restituisce size_t --> mismatch; inoltre meglio usarlo per sicurezza di conversioni implicite
		{ if (vec[i] < vec[i-1])
			{ return false; } //senno continua
		}	
	return true;
}

template<typename T>
void bubblesort(std::vector<T>& vec)
{	if (vec.size() == 0) { return; }	
	//va da 0 a n-2 (compresi) perchè servono n-1 controlli per ordinare
	for (size_t i=0; i + 1 < vec.size(); i++)		//uso size_t cosi lo considero unsigned
	
		//parte da 0 e poi dopo faccio j-1 quindi posso lasciare il primo elt fuori dal controllo (quando i = 0 vado fino a i+1=1) 
		{ for (size_t j = vec.size()-1; j > i; j--) 		
			{ if (vec[j] < vec[j-1]) {std::swap (vec[j], vec[j-1]);}
			}
		}
}


template<typename T>
void selectionsort(std::vector<T>& vec)
{	if (vec.size() == 0) { return; }	

	for (size_t i=0; i < vec.size()-1; i++) 	//servono n-1 controlli per ordinare
	{	size_t min_index = i;
		for (size_t j=i+1; j < vec.size(); j++) 
		{ if (vec[j] < vec[min_index]) {min_index = j; }  }
		if (min_index != i) {std::swap (vec[i], vec[min_index]); }
	}
}


template<typename T>
void insertionsort(std::vector<T>& vec)
{	if (vec.size() == 0) { return; }	
	
	for (size_t i=1; i < vec.size(); i++)
	{	T value = vec[i];
		int j = i-1;		//meglio usare int perchè size_t non può diventare negativo e dopo ho un while con ultima operazione di sottrazione, non un for che mi da' sicurezza
		while (j >= 0 && vec[j] > value) 
		{	vec[j+1] = vec[j];
			j--;
		}
		vec[j+1] = value;
	}
}


template<typename T>
void merge(std::vector<T>& vec, int left, int mid, int right)
{ 	if (vec.size() <= 1) { return; }
		
	int n1 = mid - left + 1;
	int n2 = right - mid;
	std::vector<T> L(n1+1);
	std::vector<T> R(n2+1);
	
	//Copio i dati in vettori temporanei
	for (int i=0; i < n1; i++)
	{ L[i] = vec[left+i]; }
	for (int j=0; j < n2; j++)
	{ R[j] = vec[mid+j+1]; }
	
	/*infinito è un placeholder(segnaposto): il mio elt più grande lo butto al fondo, poi faccio i controlli sul resto --> evito di metterlo*/
	int i = 0;
	int j = 0;
	int k = left;
	
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			vec[k] = L[i];
			i++;
		} else {
			vec[k] = R[j];
			j++;
		}
		k++;
 	}

	//Copio gli elementi rimasti in leftVec[], se ce ne sono
	while (i < n1) {
		vec[k] = L[i];
		i++;
		k++;
	}

	//Copio gli elementi rimasti in leftVec[], se ce ne sono
	while (j < n2) {
		vec[k] = R[j];
		j++;
		k++;
	}
	
	/*
	for (int k = s; k < d + 1; k ++)
	{ 	if (L[i] <= R[j]) 
			{ 	vec[k] = L[i];
				i++;
			}
		else
			{ 	vec[k] = R[j];
				j++;
			}
	} */
}

template<typename T>
void mergesort(std::vector<T>& vec, int left, int right)
{ if (left < right)	{
	int mid = std::floor( (left + right)/2 );
	mergesort(vec, left, mid);
	mergesort(vec, mid+1, right);
	merge(vec, left, mid, right);
	}
}


template<typename T>
int partition(std::vector<T>& vec, int low, int high)
{ 	auto pivot = vec[high]; 	//metto come pivot l'ultimo elemento e faccio capire il tipo ad auto 
	int i = (low-1); 		//uso l'indice dell'elt prima dell'ultimo elt per lo swap
	
	for (int j=low; j < high; j++) 
	{ if (vec[j] <= pivot) {
		 i++;
		 std::swap (vec[i], vec[j]); }
	}
	
	if (i != high) {std::swap (vec[i+1], vec[high]); }		//metto il pivot nella sua posizione
	
	return (i+1); 	//rango
}

template<typename T>
void quicksort(std::vector<T>& vec, int low, int high)
{	if (low < high) 
	{	int p = partition(vec, low, high);		//partitioning index, arr[p] è ora nel posto giusto
		quicksort(vec, low, p-1);				//ordino gli elts prima di p
		quicksort(vec, p+1, high);
	}
}


/* Dimensione al disotto della quale gli algoritmi quadratici sono più veloci degli algoritmi logaritmici: n = 42; poi vince il quicksort
Considero quindi una versione modificata di Quicksort che, al disotto di questa soglia,
utilizza l’algoritmo quadratico più veloce per fare l’ordinamento, cioè l'insertion sort. */
template<typename T>
void hybrid_quicksort(std::vector<T>& vec, int low, int high)
{ if (low < high)
	{ int n = high - low + 1; //dimensione del vettore da ordinare
		
		if (n <= 42) 
		{ 	// faccio insertion sort manuale in caso l'hybrid fosse chiamato su un sottointervallo [low, high] --> così non corrompo l'ordinamento degli altri elementi
			for (int i = low + 1; i <= high; i++) {
			auto value = vec[i];
			int j = i - 1;
			while (j >= low && vec[j] > value) {
				vec[j + 1] = vec[j];
				j--;
			}
			vec[j + 1] = value;
			} 
		}
		
		else {
			int p = partition(vec, low, high);		//partitioning index, arr[p] è ora nel posto giusto
			quicksort(vec, low, p-1);				//ordino gli elts prima di p
			quicksort(vec, p+1, high);
		}
	}
}


/* Uso questa funzione template per stampare il vettore delle dimensioni che servirà per i grafici*/
template<typename T>
void
print_vector(const std::vector<T>& v)
{	if (v.size() == 0) { return;}
	std::cout << " = [";
    for (size_t i = 0; i < v.size()-1; i++) {
        std::cout << v[i] << "; ";
    }
    std::cout << v[v.size()-1] << "];\n";
}

	