/*
--- Part Two ---

Content with the amount of tree cover available, the Elves just need to know 
the best spot to build their tree house: they would like to be able to see a 
lot of trees.

To measure the viewing distance from a given tree, look up, down, left, and 
right from that tree; stop if you reach an edge or at the first tree that is 
the same height or taller than the tree under consideration. (If a tree is 
right on the edge, at least one of its viewing distances will be zero.)

The Elves don't care about distant trees taller than those found by the rules 
above; the proposed tree house has large eaves to keep it dry, so they wouldn't 
be able to see higher than the tree house anyway.

In the example above, consider the middle 5 in the second row:

30373
25512
65332
33549
35390

    Looking up, its view is not blocked; it can see 1 tree (of height 3).
    Looking left, its view is blocked immediately; it can see only 1 tree (of 
    height 5, right next to it).
    Looking right, its view is not blocked; it can see 2 trees.
    Looking down, its view is blocked eventually; it can see 2 trees (one of 
    height 3, then the tree of height 5 that blocks its view).

A tree's scenic score is found by multiplying together its viewing distance in 
each of the four directions. For this tree, this is 4 (found by multiplying 1 * 
1 * 2 * 2).

However, you can do even better: consider the tree of height 5 in the middle of 
the fourth row:

30373
25512
65332
33549
35390

    Looking up, its view is blocked at 2 trees (by another tree with a height 
    of 5).
    Looking left, its view is not blocked; it can see 2 trees.
    Looking down, its view is also not blocked; it can see 1 tree.
    Looking right, its view is blocked at 2 trees (by a massive tree of height 
    9).

This tree's scenic score is 8 (2 * 2 * 1 * 2); this is the ideal spot for the 
tree house.

Consider each tree on your map. What is the highest scenic score possible for 
any tree?
*/

// Compilar con:
// g++ Day8_2.cpp -o Day8_2.exe

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> direcciones_cardinales;

pair<int, int> operator +(const pair<int, int> &a, const pair<int, int> &b) {
	return pair<int, int>(a.first + b.first, a.second + b.second);
}

pair<int, int> & operator +=(pair<int, int> &a, const pair<int, int> &b) {
	return a = (a + b);
}

bool puedeMoverse(pair<int, int> posicion, pair<int, int> direccion,
					const vector<vector<int>> &arboles) {
	pair<int, int> nueva_pos = posicion + direccion;
	int new_x = nueva_pos.first;
	int new_y = nueva_pos.second;
	
	if(new_x < 0 || new_y < 0) return false;
	if(new_x >= arboles.at(0).size() || new_y >= arboles.size()) return false;
	
	return true;
}

bool puedeVerse(pair<int, int> posicion, const vector<vector<int>> &arboles) {
	int arbol = arboles[posicion.first][posicion.second];
	
	for(pair<int, int> direccion : direcciones_cardinales) {
		pair<int, int> nueva_pos = posicion;
		bool puedeVerse = true;
		
		while(puedeMoverse(nueva_pos, direccion, arboles)) {
			nueva_pos += direccion;
			if(arboles[nueva_pos.first][nueva_pos.second] >= arbol) {
				puedeVerse = false;
				break;
			}
		}
		
		if(puedeVerse) return true;
	}
	
	return false;
}

int VeArboles(pair<int, int> posicion, pair<int, int> direccion,
				const vector<vector<int>> &arboles){
	int num_arboles = 0;
	int arbol = arboles[posicion.first][posicion.second];
	
	while(puedeMoverse(posicion, direccion, arboles)) {
		num_arboles ++;
		posicion += direccion;
		if(arboles[posicion.first][posicion.second] >= arbol) break;
	}
	
	return num_arboles;
}

int main(int argc, char *argv[]){
	direcciones_cardinales.push_back(pair<int, int>(1, 0));
	direcciones_cardinales.push_back(pair<int, int>(0, 1));
	direcciones_cardinales.push_back(pair<int, int>(-1, 0));
	direcciones_cardinales.push_back(pair<int, int>(0, -1));
	
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
	getline(arch_entrada, linea_actual);
	vector<vector<int>>arboles;
	int fila = 0;
	
	while(!arch_entrada.eof()) {
		arboles.push_back(vector<int>());
		
		for(char letra : linea_actual) {
			arboles[fila].push_back(letra - '0');
		}
		
		fila++;
		getline(arch_entrada, linea_actual);
	}
	
	int maxVisiPunt = 0;
	
	for(int fila = 1; fila < arboles.size()-1; fila++) {
		for(int columna = 1; columna < arboles[fila].size()-1; columna++) {
			int punt = 1;
			for(pair<int, int> direccion : direcciones_cardinales) {
				punt *= VeArboles(pair<int, int>(fila, columna), direccion, 
								  arboles);
			}
			maxVisiPunt = punt > maxVisiPunt ? punt : maxVisiPunt;
		}
	}
	
	cout << "Max: " << maxVisiPunt << endl;
	
	return 0;
}

// Es > 129










