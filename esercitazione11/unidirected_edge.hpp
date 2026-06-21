#pragma once
#include <ostream> 
#include <algorithm> 	//per std::min e std::max

/*non devo usare add_node(), quindi devo fare una struttura guidata dagli archi. I nodi vengono aggiunti implicitamente all'inserimento degli archi */ 
template <typename T>
class unidirected_edge {
	T from_;
	T to_;
	
public:
	/*Costruttore user-defined; devo fare in modo che from sia sempre minore di to */
	//per chiamarlo uso 	unidirected_edge<T> e(u,v); e mi salva l'arco in e, ordinandomi i nodi estremi 
	unidirected_edge (const T& u, const T& v): from_(std::min(u,v)), to_(std::max(u,v)) {}   
		
	/* Restituiscono i valori del nodo di partenza e di arrivo dell'arco */    
    const T& from() const { return from_; }
    const T& to() const { return to_; }
    
    /*Ordine lessicografico*/
    //metto const perchè questa funzione non modifica l'oggetto su cui viene chiamata, cioè {*this}
    bool operator<(const unidirected_edge& other) const		
    {	
	    // return (from_ < other.from_) || (from_ == other.from_ && to_ <  other.to_);
	    
	    if (from_ != other.from_) { return from_ < other.from_; }
    	return to_ < other.to_; 
	}
	
	bool operator==(const unidirected_edge& other) const
	{	return from_ == other.from_ && to_ == other.to_; 	}
	
};
	
/*operatore di stampa dell'arco, come funzione libera, fuori dalla classe; metto lo stesso template T della classe e accedo ai membri pubblici from() e to(); se lo definissi nella classe, avrei che ci sarebbe come argomento {*this}, e quindi non sarebbe uno stream che si può mettere in cout o << */
template <typename T>
std::ostream& operator<<(std::ostream& os, const unidirected_edge<T>& e) {
	os << "(" << e.from() << ", " << e.to() << ")";
	return os;
}
