#include <iostream> 
#include <algorithm>
#include <cmath>

int main()
{
	static const int N = 10;
	double arr[N] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
	double min_val = arr[0];
	double max_val = arr[0];
	
	//calcolo massimo e minimo
	min_val = *std::min_element(arr, arr+N);
	max_val = *std::max_element(arr, arr+N);
	std:: cout <<"The minimum value is " << min_val << "\n";
	std:: cout <<"The maximum value is " << max_val << "\n";
	
	//calcolo della media
	double sum = 0.0;
	for (int i = 0; i < N; i++) {
		sum += arr[i];
	}
	double avg = sum/N;
	std::cout << "The average is " << avg << "\n";
	
	//calcolo della deviazione standard: calcolo prima la varianza*N (var) come media degli scarti quadratici, poi la divido per N e poi ne faccio la radice
	double var = 0.0;
	for (int i = 0; i < N; i++) {
		var += (arr[i]-avg)*(arr[i]-avg);
	}
	double dev = std::sqrt(var/N);
	std::cout << "The standard deviation is " << dev << "\n";
	return 0;
}