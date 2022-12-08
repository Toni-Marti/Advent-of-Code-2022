/*
--- Part Two ---

It seems like there is still quite a bit of duplicate work planned. Instead, 
the Elves would like to know the number of pairs that overlap at all.

In the above example, the first two pairs (2-4,6-8 and 2-3,4-5) don't overlap, 
while the remaining four pairs (5-7,7-9, 2-8,3-7, 6-6,4-6, and 2-6,4-8) do 
overlap:

    5-7,7-9 overlaps in a single section, 7.
    2-8,3-7 overlaps all of the sections 3 through 7.
    6-6,4-6 overlaps in a single section, 6.
    2-6,4-8 overlaps in sections 4, 5, and 6.

So, in this example, the number of overlapping assignment pairs is 4.

In how many assignment pairs do the ranges overlap?
*/

// Compilar con:
// g++ Day4_2.cpp -o Day4_2.exe

using namespace std;

#include <iostream>
#include <fstream>

bool se_solapan(int a, int b, int c, int d) {
	return (a >= c && a <= d) || (b >= c && b <= d) || (a <= c && b >= d);
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
	
	int total = 0;
	int prim_inf, prim_sup, seg_inf, seg_sup;
	char basura;
	
	arch_entrada >> prim_inf;
	arch_entrada >> basura;
	arch_entrada >> prim_sup;
	arch_entrada >> basura;
	arch_entrada >> seg_inf;
	arch_entrada >> basura;
	arch_entrada >> seg_sup;
	
	do {
		if(se_solapan(prim_inf, prim_sup, seg_inf, seg_sup))
			total++;
		
		arch_entrada >> prim_inf;
		arch_entrada >> basura;
		arch_entrada >> prim_sup;
		arch_entrada >> basura;
		arch_entrada >> seg_inf;
		arch_entrada >> basura;
		arch_entrada >> seg_sup;
	} while(!arch_entrada.eof());
	
	cout << "Total: " << total << endl;
	
	return 0;
}










