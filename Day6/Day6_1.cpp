/*
ENUNCIADO
*/

// Compilar con:
// g++ Day6_1.cpp -o Day6_1.exe

#include <iostream>
#include <fstream>
#include <set>

using namespace std;

bool hay4Distinntos(string entrada, const int posicion) {
	const int NUM_DISTINTOS = 4;
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
	for(i=3; i<entrada.length(); i++) {
		if(hay4Distinntos(entrada, i)) break;
	}
	
	cout << "Sucede en el caracter " << (i + 1) << endl;
	
	return 0;
}










