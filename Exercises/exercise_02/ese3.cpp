#include <iostream> 

int main()
{
	static const int N = 10;
	double arr[N] = {8, 34.7, 89.0, 3.3, 54.0, 5.5, 2.2, 7.7, 4.4, 9.9};
	
	bool scambi = 1;
	while (scambi == 1) {
		scambi = 0;
		for (int i = 0; i < N-1; i++) {
			if (arr[i] > arr[i+1]) {
				double nuovo = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = nuovo;
				scambi = 1;
			}
		}
	}
	
	for (int j = 0; j < N; j++) {
		std::cout << arr[j] << " ";
	}
	
	return 0;
}
