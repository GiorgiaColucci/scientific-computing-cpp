#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char*argv[]) {
	if (argc < 2) {
		cerr << "Errore: devi specificare il nome del file \n";
		return 1;
	}
	
	string filename = argv[1];
	ifstream ifs(filename);
	
	if (!ifs.is_open()) {
		cerr << "Errore: impossibile aprire il file" << filename << " \n";
		return 1;
	}
		 
	for (int i = 0; i < 3; i++) {
		string city;
		double temp1, temp2, temp3, temp4;
		double avg;
		
		ifs >> city >> temp1 >> temp2 >> temp3 >> temp4;
		avg = (temp1 + temp2 + temp3 + temp4)/4;
		
		cout << "La temperatura media a " << city << " è di " << avg << " gradi " << "\n";
	}
	return 0;
}