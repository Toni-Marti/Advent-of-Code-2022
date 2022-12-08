/*
ENUNCIADO
*/

// Compilar con:
// g++ Day6_2.cpp -o Day6_2.exe

#include <iostream>
#include <fstream>
#include <set>

using namespace std;

const int NUM_DISTINTOS = 14;

bool hayDistinntos(string entrada, const int posicion) {
	set<char> letras;
	for(int i=0; i < NUM_DISTINTOS; i++) {
		if(!letras.insert(entrada[posicion-i]).second) return false;
	}
	
	return true;
};

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
	
	string entrada;
	
	arch_entrada >> entrada;
	
	int i;
	for(i = NUM_DISTINTOS-1; i<entrada.length(); i++) {
		if(hayDistinntos(entrada, i)) break;
	}
	
	cout << "Sucede en el caracter " << (i + 1) << endl;
	
	return 0;
}










