//STACK
#pragma once
#include <list>
template <typename T>
class lifo {
	std::list<T> s;
	public:
		lifo() {
			s = {};
		}
		
		void put(const T& elem){
			s.push_front(elem);
		}

		T get() {
			T elem = s.front();
			s.pop_front();
			return elem; 
		}

		bool empty() const{
			return s.empty();
		}

};