#pragma once
template<typename T>
class edge { 
	T edge_from;
	T edge_to;
	public:
		edge(const T& a, const T& b) {
			if (a < b) {
				edge_from = a;
				edge_to = b;
			}
			else {
				edge_from = b;
				edge_to = a;
			}
		}
		
		const T& from() const {
			return edge_from;
		}
		
		const T& to() const {
			return edge_to;
		}
		
		bool operator< (const edge& e_2) const {
			const T& from_2 = e_2.from();
			const T& to_2 = e_2.to();
			if (edge_from < from_2 || (edge_from== from_2 && edge_to < to_2) ) {
				return true;
			}
			else {
				return false;
			}			
		}
		
		bool operator== (const edge& e_2) const {
			const T& from_2 = e_2.from();
			const T& to_2 = e_2.to();
			if (edge_from == from_2 && edge_to == to_2) {
				return true;
			}
			else {
				return false;
			}
		}
};