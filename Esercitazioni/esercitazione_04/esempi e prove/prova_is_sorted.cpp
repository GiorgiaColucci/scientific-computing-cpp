#include <iostream> 
#include <vector> 
#include "randfiller.h"  

#include "sort.hpp" 

template<typename T> 
void 
print_vector(const std::vector<T>& v) 
{ 
	for (size_t i = 0; i < v.size(); i++) { 
		std::cout << v[i] << " "; 
	} 
	std::cout << "\n"; 
} 

int main(void) 
{ 
	randfiller rf; /* instantiate a randfiller */ 
	
	std::vector<int> vi; 
	vi.resize(10); 	//oppure potevo direttamente fare vi(10) nella riga sopra
	rf.fill(vi, 30, 50); /* use it on vectors */ 
	print_vector(vi); 
	std::cout << is_sorted(vi) << "\n";
	
	std::vector<float> vf; 
	vf.resize(5); 
	rf.fill(vf, 1.5f, 7.5f); 
	print_vector(vf); 
	std::cout << is_sorted(vf) << "\n";
	
	std::vector<double> vd; 
	vd.resize(8); 
	rf.fill(vd, 1.5, 7.5); 
	print_vector(vd); 
	std::cout << is_sorted(vd) << "\n";
	
	/* //PROVE
	std::vector<int> test1 = {};
	print_vector(test1);
	std::vector<int> test2 = {4,3,2,1};
	print_vector(test2);

	std::cout << "Test ordinato: " << is_sorted(test1) << "\n";
	std::cout << "Test NON ordinato: " << is_sorted(test2) << "\n";
	*/
	
	return 0;
}