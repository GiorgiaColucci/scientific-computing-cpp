#pragma once
#include <queue>		//per FiFo, cioè per BFS (Ampiezza)
#include <stack>		//per LiFo, cioè per DFS (Profondità)

template<typename T>
class fifo {
private:
	std::queue<T> q;
	
public:
	fifo() = default;
	
	void put(const T& x)
	{ q.push(x); }
	
	T get() //rimuove il primo elemento (First) e lo restituisce in x 
	{ 	T x = q.front();
		q.pop();
		return x; 
	}
		
	bool empty() const
	{ return q.empty(); }
};


template<typename T>
class lifo {
private: 
	std::stack<T> s;
	
public:
	lifo() = default;
	
	void put(const T& x)
	{ s.push(x); }
	
	T get() //rimuove il primo elemento (Last) e lo restituisce in x 
	{ 	T x = s.top();
		s.pop();
		return x; 
	}
		
	bool empty() const
	{ return s.empty(); }
};