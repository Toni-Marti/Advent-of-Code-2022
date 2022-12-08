/*
--- Part Two ---

As you finish identifying the misplaced items, the Elves come to you with 
another issue.

For safety, the Elves are divided into groups of three. Every Elf carries a 
badge that identifies their group. For efficiency, within each group of three 
Elves, the badge is the only item type carried by all three Elves. That is, if 
a group's badge is item type B, then all three Elves will have item type B 
somewhere in their rucksack, and at most two of the Elves will be carrying any 
other item type.

The problem is that someone forgot to put this year's updated authenticity 
sticker on the badges. All of the badges need to be pulled out of the rucksacks 
so the new authenticity stickers can be attached.

Additionally, nobody wrote down which item type corresponds to each group's 
badges. The only way to tell which item type is the right one is by finding the 
one item type that is common between all three Elves in each group.

Every set of three lines in your list corresponds to a single group, but each 
group can have a different badge item type. So, in the above example, the first 
group's rucksacks are the first three lines:

vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg

And the second group's rucksacks are the next three lines:

wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw

In the first group, the only item type that appears in all three rucksacks is 
lowercase r; this must be their badges. In the second group, their badge item 
type must be Z.

Priorities for these items must still be found to organize the sticker 
attachment efforts: here, they are 18 (r) for the first group and 52 (Z) for 
the second group. The sum of these is 70.

Find the item type that corresponds to the badges of each three-Elf group. 
What is the sum of the priorities of those item types?
*/

// Compilar con:
// g++ Day3_2.cpp -o Day3_2.exe

using namespace std;

#include <iostream>
#include <fstream>
#include <set>
#include <vector>

template<typename T>
void ImprimeSet(set<T> conjunto) {
	for(T elemento : conjunto) {
		cout << elemento;
	}
}

int Prioridad(char letra) {
	if(letra >= 'a' && letra <= 'z') {
		return letra - 'a' + 1;
	}
	else {
		return 26 + letra - 'A' + 1;
	}
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
	
	vector<string> mochilas(3, "");
	arch_entrada >> mochilas[0];
	arch_entrada >> mochilas[1];
	arch_entrada >> mochilas[2];
	int suma_prio = 0;
	
	do {
		// Insertamos los elementos de cada mocihla en un set
		vector<set<char>> items_m(3);
		
		for(int i=0; i<3; i++) {
			for(char letra : mochilas[i]) {
				items_m[i].insert(letra);
			}
		}
		
		char badage;
		
		// Buscamos cual es el que se repite
		for(char elemento : items_m[0]) {
			// Si esta en los tres lo hemos encontrado
			if(items_m[1].find(elemento) != items_m[1].end() && 
			   items_m[2].find(elemento) != items_m[2].end()) {
				badage = elemento;
				break;
			}
		}
		
		suma_prio += Prioridad(badage);
		
		arch_entrada >> mochilas[0];
		arch_entrada >> mochilas[1];
		arch_entrada >> mochilas[2];
		
	} while(!arch_entrada.eof());
	
	cout << "Prioridad total: " << suma_prio << endl;
	
	return suma_prio;
}







