#pragma once 
#include <vector>
#include <algorithm>	//per swap

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

	