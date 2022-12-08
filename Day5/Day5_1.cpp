/*
--- Day 5: Supply Stacks ---

The expedition can depart as soon as the final supplies have been unloaded from 
the ships. Supplies are stored in stacks of marked crates, but because the 
needed supplies are buried under many other crates, the crates need to be 
rearranged.

The ship has a giant cargo crane capable of moving crates between stacks. To 
ensure none of the crates get crushed or fall over, the crane operator will 
rearrange them in a series of carefully-planned steps. After the crates are 
rearranged, the desired crates will be at the top of each stack.

The Elves don't want to interrupt the crane operator during this delicate 
procedure, but they forgot to ask her which crate will end up where, and they 
want to be ready to unload them as soon as possible so they can embark.

They do, however, have a drawing of the starting stacks of crates and the 
rearrangement procedure (your puzzle input). For example:

    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2

In this example, there are three stacks of crates. Stack 1 contains two crates: 
crate Z is on the bottom, and crate N is on top. Stack 2 contains three crates; 
from bottom to top, they are crates M, C, and D. Finally, stack 3 contains a 
single crate, P.

Then, the rearrangement procedure is given. In each step of the procedure, a 
quantity of crates is moved from one stack to a different stack. In the first 
step of the above rearrangement procedure, one crate is moved from stack 2 to 
stack 1, resulting in this configuration:

[D]        
[N] [C]    
[Z] [M] [P]
 1   2   3 

In the second step, three crates are moved from stack 1 to stack 3. Crates are 
moved one at a time, so the first crate to be moved (D) ends up below the 
second and third crates:

        [Z]
        [N]
    [C] [D]
    [M] [P]
 1   2   3

Then, both crates are moved from stack 2 to stack 1. Again, because crates are 
moved one at a time, crate C ends up below crate M:

        [Z]
        [N]
[M]     [D]
[C]     [P]
 1   2   3

Finally, one crate is moved from stack 1 to stack 2:

        [Z]
        [N]
        [D]
[C] [M] [P]
 1   2   3

The Elves just need to know which crate will end up on top of each stack; in 
this example, the top crates are C in stack 1, M in stack 2, and Z in stack 3, 
so you should combine these together and give the Elves the message CMZ.

After the rearrangement procedure completes, what crate ends up on top of each 
stack?
*/

// Compilar con:
// g++ Day5_1.cpp -o Day5_1.exe

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;


template<typename T>
void InviertePila(stack<T> &pila) {
	stack<T> pila_aux = pila;
	
	while(!pila.empty()) pila.pop();
	
	while(!pila_aux.empty()) {
		pila.push(pila_aux.top());
		pila_aux.pop();
	}
}



template<typename T>
void ImprimePila(stack<T> pila) {
	InviertePila(pila);
	
	while(!pila.empty()) {
		cout << pila.top() << " ";
		pila.pop();
	}
}

template<typename T>
void ImprimePilas(const vector<stack<T>> pilas) {
	int num_pila = 1;
	int num_cajas = 0;
	for(stack<T> pila : pilas) {
		cout << "Pila " << num_pila << ": ";
		ImprimePila(pila);
		cout << endl;
		num_pila++;
		num_cajas += pila.size();
	}
	cout << "NUMERO CAJAS: " << num_cajas << endl;
}

int main(int argc, char *argv[]){
	// abrimos el archivo de entrada
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
	
	
	// Inicializamos las pilas de cajas
	string actual_line;
	getline(arch_entrada, actual_line);
	int cols = (actual_line.length() + 1) / 4;
	vector<stack<char>> pilas(cols);
	
	bool fin_inicializacion = false;
	
	while(!fin_inicializacion) {
		if(actual_line[1] != '1') {
			for(int i=0; i<cols; i++) {
				char caja = actual_line[1 + 4*i];
				
				if(caja != ' ') {
					pilas[i].push(caja);
				}
			}	
		} 
		else fin_inicializacion = true;
		
		getline(arch_entrada, actual_line);
	}
	
	for(stack<char> &pila : pilas) {
		InviertePila(pila);
	}
	
	
	// Procesamos los movimientos
	string basura;
	int cantidad, desde, hasta;
	
	arch_entrada >> basura;
	while(!arch_entrada.eof()) {
		
		arch_entrada >> cantidad;
		arch_entrada >> basura;
		arch_entrada >> desde;
		arch_entrada >> basura;
		arch_entrada >> hasta;
		
		for(int i=0; i<cantidad; i++) {
			pilas[hasta-1].push(pilas[desde-1].top());
			pilas[desde-1].pop();
		}
		
		arch_entrada >> basura;
	}
	
	
	// Obtenemos el resultado
	string resultado;
	
	for(stack<char> pila : pilas) {
		resultado += pila.top();
	}
	
	cout << "Resultado: " << resultado << endl;
	
	return 0;
}
