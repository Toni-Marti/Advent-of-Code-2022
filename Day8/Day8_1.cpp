/*
--- Day 8: Treetop Tree House ---

The expedition comes across a peculiar patch of tall trees all planted 
carefully in a grid. The Elves explain that a previous expedition planted 
these trees as a reforestation effort. Now, they're curious if this would be 
a good location for a tree house.

First, determine whether there is enough tree cover here to keep a tree house 
hidden. To do this, you need to count the number of trees that are visible from 
outside the grid when looking directly along a row or column.

The Elves have already launched a quadcopter to generate a map with the height 
of each tree (your puzzle input). For example:

30373
25512
65332
33549
35390

Each tree is represented as a single digit whose value is its height, where 0 
is the shortest and 9 is the tallest.

A tree is visible if all of the other trees between it and an edge of the grid 
are shorter than it. Only consider trees in the same row or column; that is, 
only look up, down, left, or right from any given tree.

All of the trees around the edge of the grid are visible - since they are 
already on the edge, there are no trees to block the view. In this example, 
that only leaves the interior nine trees to consider:

    The top-left 5 is visible from the left and top. (It isn't visible from the 
    right or bottom since other trees of height 5 are in the way.)
    The top-middle 5 is visible from the top and right.
    The top-right 1 is not visible from any direction; for it to be visible, 
    there would need to only be trees of height 0 between it and an edge.
    The left-middle 5 is visible, but only from the right.
    The center 3 is not visible from any direction; for it to be visible, there 
    would need to be only trees of at most height 2 between it and an edge.
    The right-middle 3 is visible from the right.
    In the bottom row, the middle 5 is visible, but the 3 and 4 are not.

With 16 trees visible on the edge and another 5 visible in the interior, a 
total of 21 trees are visible in this arrangement.

Consider your map; how many trees are visible from outside the grid?
*/

// Compilar con:
// g++ Day8_1.cpp -o Day8_1.exe

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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
	vector<pair<int, int>> direcciones;
	direcciones.push_back(pair<int, int>(1, 0));
	direcciones.push_back(pair<int, int>(0, 1));
	direcciones.push_back(pair<int, int>(-1, 0));
	direcciones.push_back(pair<int, int>(0, -1));
	
	for(pair<int, int> direccion : direcciones) {
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
	
	int visibles = 0;
	
	for(int fila = 0; fila < arboles.size(); fila++) {
		for(int columna = 0; columna < arboles[fila].size(); columna++) {
			visibles += puedeVerse(pair<int, int>(fila, columna), arboles);
		}
	}
	
	cout << "Visibles: " << visibles << endl;
	
	return 0;
}










