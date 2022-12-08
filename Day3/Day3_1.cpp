/*
--- Day 3: Rucksack Reorganization ---

One Elf has the important job of loading all of the rucksacks with supplies for 
the jungle journey. Unfortunately, that Elf didn't quite follow the packing 
instructions, and so a few items now need to be rearranged.

Each rucksack has two large compartments. All items of a given type are meant 
to go into exactly one of the two compartments. The Elf that did the packing 
failed to follow this rule for exactly one item type per rucksack.

The Elves have made a list of all of the items currently in each rucksack (your 
puzzle input), but they need your help finding the errors. Every item type is 
identified by a single lowercase or uppercase letter (that is, a and A refer to 
different types of items).

The list of items for each rucksack is given as characters all on a single 
line. A given rucksack always has the same number of items in each of its two 
compartments, so the first half of the characters represent items in the first 
compartment, while the second half of the characters represent items in the 
second compartment.

For example, suppose you have the following list of contents from six rucksacks:

vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw

    The first rucksack contains the items vJrwpWtwJgWrhcsFMMfFFhFp, which means 
    its first compartment contains the items vJrwpWtwJgWr, while the second 
    compartment contains the items hcsFMMfFFhFp. The only item type that 
    appears in both compartments is lowercase p.
    The second rucksack's compartments contain jqHRNqRjqzjGDLGL and 
    rsFMfFZSrLrFZsSL. The only item type that appears in both compartments is 
    uppercase L.
    The third rucksack's compartments contain PmmdzqPrV and vPwwTWBwg; the only 
    common item type is uppercase P.
    The fourth rucksack's compartments only share item type v.
    The fifth rucksack's compartments only share item type t.
    The sixth rucksack's compartments only share item type s.

To help prioritize item rearrangement, every item type can be converted to a 
priority:

    Lowercase item types a through z have priorities 1 through 26.
    Uppercase item types A through Z have priorities 27 through 52.

In the above example, the priority of the item type that appears in both 
compartments of each rucksack is 16 (p), 38 (L), 42 (P), 22 (v), 20 (t), and 19 
(s); the sum of these is 157.

Find the item type that appears in both compartments of each rucksack. What is 
the sum of the priorities of those item types?
*/

// Compilar con:
// g++ Day3_1.cpp -o Day3_1.exe

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
	
	string mochila;
	arch_entrada >> mochila;
	int suma_prio = 0;
	
	do {
		set<char> mitad1;
		set<char> mitad2;
		// Insertamos la mitad de las letras en cada mochila
		for(int i=0; i< mochila.length()/2; i++) {
			mitad1.insert(mochila[i]);
			mitad2.insert(mochila[mochila.length()-1-i]);
		}
		
		// Encontramos los repetidos
		set<char> repetidas;
		
		for(set<char>::iterator mitad1_it = mitad1.begin();
			mitad1_it != mitad1.end(); mitad1_it++) {
			
			if(mitad2.find(*mitad1_it) != mitad2.end()) {
				repetidas.insert(*mitad1_it);
			}
		}
		
		// Sumamos sus prioridades
		for(set<char>::iterator rep_it = repetidas.begin();
			rep_it != repetidas.end(); rep_it++) {
			suma_prio += Prioridad(*rep_it);
		}
		
		arch_entrada >> mochila;
		
	} while(!arch_entrada.eof());
	
	cout << "Prioridad total: " << suma_prio << endl;
	
	return suma_prio;
}







