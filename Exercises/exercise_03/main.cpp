#include <iostream>
#include "header.hpp"

// stampo i risultati chiamando operator<< definito nell'header
int main()
{
    //int a = 5;
    rational<int> a(-5,4);
    //int b = 8;
    rational<int> b(2, 3);
    
    rational<int> sum1 = a + b;
    rational<int> diff1 = a - b;
    rational<int> prod1 = a * b;
    rational<int> div1 = a / b;
    std::cout << "Primo operando: " << a << " secondo operando: " << b << "\n";
    std::cout << "La somma è " << sum1 << "\n";		/* sto chiamando automaticamente operator<<*/
    std::cout << "La differenza è " << diff1 << "\n";
    std::cout << "Il prodotto è " << prod1 << "\n";
    std::cout << "La divisione è " << div1 << "\n";
    
	rational<int> sum = b + a;
    rational<int> diff = b - a;
    rational<int> prod = b * a;
    rational<int> div = b / a;
    std::cout << "Primo operando: " << b << " secondo operando: " << a << "\n";
    std::cout << "La somma è " << sum << "\n";		/* sto chiamando automaticamente operator<<*/
    std::cout << "La differenza è " << diff << "\n";
    std::cout << "Il prodotto è " << prod << "\n";
    std::cout << "La divisione è " << div << "\n";    return 0;
}

