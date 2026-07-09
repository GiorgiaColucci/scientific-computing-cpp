//CODA
#pragma once
#include <list>
template <typename T>
class fifo {
	std::list<T> q;
	public:
		fifo() {
			q = {};
		}
		
		void put(const T& elem){
			q.push_back(elem);
		}

		T get() {
			T elem = q.front();
			q.pop_front();
			return elem;
		};

		bool empty() const{ 
			return q.empty();
		}
};