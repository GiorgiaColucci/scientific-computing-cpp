#pragma once
#include <iostream>
#include "edge.hpp"
template<typename I>
std::ostream& operator<<(std::ostream& os, const edge<I>& e) {
	I nodo_f = e.from();
	I nodo_t = e.to();
	os << "(" << nodo_f << ", " << nodo_t << ")";
	return os;
}