/*
--- Part Two ---

By the time you calculate the answer to the Elves' question, they've already 
realized that the Elf carrying the most Calories of food might eventually run 
out of snacks.

To avoid this unacceptable situation, the Elves would instead like to know the 
total Calories carried by the top three Elves carrying the most Calories. That 
way, even if one of those Elves runs out of snacks, they still have two backups.

In the example above, the top three Elves are the fourth Elf (with 24000 
Calories), then the third Elf (with 11000 Calories), then the fifth Elf (with 
10000 Calories). The sum of the Calories carried by these three elves is 45000.

Find the top three Elves carrying the most Calories. How many Calories are 
those Elves carrying in total?
*/

// Compilar con:
// g++ Day1_2.cpp -o Day1_2.exe

#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <list>

using namespace std;

int main(int argc, char *argv[]){
	ifstream arch_entrada;
	string ruta_arch = "Entrada.txt";
	
	if(argc > 2) {
		cerr << "ERROR: Demasiados argumentos." << endl;
		return -1;
	}
	else if( argc == 2) {
		ruta_arch = argv[1];
	}
	
	arch_entrada.open(ruta_arch);
	
	if(!arch_entrada.is_open()) {
		cerr << "ERROR: No se pudo abrir el archivo: " << ruta_arch << endl;
		return -2;
	}
	
	string linea_actual;
	int INT_MIN = numeric_limits<int>::min();
	const int NUM_MAXS = 3;
	list <int> maxs(NUM_MAXS, INT_MIN);
	int suma = 0;
	
	while(!getline(arch_entrada,linea_actual).eof()) {
		if(linea_actual.empty()) {
			for(list<int>::iterator it = maxs.begin(); it != maxs.end(); it++){
				if(suma > *it) {
					maxs.insert(it, suma);
					maxs.pop_back();
					break;
				}
			}
			suma = 0;
		}
		else {
			suma += stoi(linea_actual);
		}
	}
	
	int total = 0;
	
	for(list<int>::iterator it = maxs.begin(); it != maxs.end(); it++) {
		total += *it;
		cout << *it << endl;
	}
	cout << maxs.size() << endl;;
	cout << "La suma de los " << NUM_MAXS << " maximos es: " << total << endl;
	return total;
}
