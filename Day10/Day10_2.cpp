/*
--- Part Two ---

It seems like the X register controls the horizontal position of a sprite. 
Specifically, the sprite is 3 pixels wide, and the X register sets the 
horizontal position of the middle of that sprite. (In this system, there is no 
such thing as "vertical position": if the sprite's horizontal position puts its 
pixels where the CRT is currently drawing, then those pixels will be drawn.)

You count the pixels on the CRT: 40 wide and 6 high. This CRT screen draws the 
top row of pixels left-to-right, then the row below that, and so on. The 
left-most pixel in each row is in position 0, and the right-most pixel in each 
row is in position 39.

Like the CPU, the CRT is tied closely to the clock circuit: the CRT draws a 
single pixel during each cycle. Representing each pixel of the screen as a #, 
here are the cycles during which the first and last pixel in each row are drawn:

Cycle   1 -> ######################################## <- Cycle  40
Cycle  41 -> ######################################## <- Cycle  80
Cycle  81 -> ######################################## <- Cycle 120
Cycle 121 -> ######################################## <- Cycle 160
Cycle 161 -> ######################################## <- Cycle 200
Cycle 201 -> ######################################## <- Cycle 240

So, by carefully timing the CPU instructions and the CRT drawing operations, 
you should be able to determine whether the sprite is visible the instant each 
pixel is drawn. If the sprite is positioned such that one of its three pixels 
is the pixel currently being drawn, the screen produces a lit pixel (#); 
otherwise, the screen leaves the pixel dark (.).

The first few pixels from the larger example above are drawn as follows:

Sprite position: ###.....................................

Start cycle   1: begin executing addx 15
During cycle  1: CRT draws pixel in position 0
Current CRT row: #

During cycle  2: CRT draws pixel in position 1
Current CRT row: ##
End of cycle  2: finish executing addx 15 (Register X is now 16)
Sprite position: ...............###......................

Start cycle   3: begin executing addx -11
During cycle  3: CRT draws pixel in position 2
Current CRT row: ##.

During cycle  4: CRT draws pixel in position 3
Current CRT row: ##..
End of cycle  4: finish executing addx -11 (Register X is now 5)
Sprite position: ....###.................................

Start cycle   5: begin executing addx 6
During cycle  5: CRT draws pixel in position 4
Current CRT row: ##..#

During cycle  6: CRT draws pixel in position 5
Current CRT row: ##..##
End of cycle  6: finish executing addx 6 (Register X is now 11)
Sprite position: ..........###...........................

Start cycle   7: begin executing addx -3
During cycle  7: CRT draws pixel in position 6
Current CRT row: ##..##.

During cycle  8: CRT draws pixel in position 7
Current CRT row: ##..##..
End of cycle  8: finish executing addx -3 (Register X is now 8)
Sprite position: .......###..............................

Start cycle   9: begin executing addx 5
During cycle  9: CRT draws pixel in position 8
Current CRT row: ##..##..#

During cycle 10: CRT draws pixel in position 9
Current CRT row: ##..##..##
End of cycle 10: finish executing addx 5 (Register X is now 13)
Sprite position: ............###.........................

Start cycle  11: begin executing addx -1
During cycle 11: CRT draws pixel in position 10
Current CRT row: ##..##..##.

During cycle 12: CRT draws pixel in position 11
Current CRT row: ##..##..##..
End of cycle 12: finish executing addx -1 (Register X is now 12)
Sprite position: ...........###..........................

Start cycle  13: begin executing addx -8
During cycle 13: CRT draws pixel in position 12
Current CRT row: ##..##..##..#

During cycle 14: CRT draws pixel in position 13
Current CRT row: ##..##..##..##
End of cycle 14: finish executing addx -8 (Register X is now 4)
Sprite position: ...###..................................

Start cycle  15: begin executing addx 13
During cycle 15: CRT draws pixel in position 14
Current CRT row: ##..##..##..##.

During cycle 16: CRT draws pixel in position 15
Current CRT row: ##..##..##..##..
End of cycle 16: finish executing addx 13 (Register X is now 17)
Sprite position: ................###.....................

Start cycle  17: begin executing addx 4
During cycle 17: CRT draws pixel in position 16
Current CRT row: ##..##..##..##..#

During cycle 18: CRT draws pixel in position 17
Current CRT row: ##..##..##..##..##
End of cycle 18: finish executing addx 4 (Register X is now 21)
Sprite position: ....................###.................

Start cycle  19: begin executing noop
During cycle 19: CRT draws pixel in position 18
Current CRT row: ##..##..##..##..##.
End of cycle 19: finish executing noop

Start cycle  20: begin executing addx -1
During cycle 20: CRT draws pixel in position 19
Current CRT row: ##..##..##..##..##..

During cycle 21: CRT draws pixel in position 20
Current CRT row: ##..##..##..##..##..#
End of cycle 21: finish executing addx -1 (Register X is now 20)
Sprite position: ...................###..................

Allowing the program to run to completion causes the CRT to produce the 
following image:

##..##..##..##..##..##..##..##..##..##..
###...###...###...###...###...###...###.
####....####....####....####....####....
#####.....#####.....#####.....#####.....
######......######......######......####
#######.......#######.......#######.....

Render the image given by your program. What eight capital letters appear on 
your CRT?
*/

// Compilar con:
// g++ Day10_2.cpp -o Day10_2.bin

#include <iostream>
#include <fstream>

using namespace std;

bool contenido_en(int val, int min, int max) {
	return val >= min && val <= max;
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
	
	int ciclo = 0; // Mide el ciclo en el que se encuntra el programa, es
				   // lo primero que se actualiza al iniciar un ciclo nuevo
	string ultima_instruccion; // Contiene la ultima intruccion que se ha leido
	int val; // Si la instruccion pasa un valor, se almecena aqui
	int ciclos_restantes_instr = 0; // Indica cuantos cilos le quedan a la
									// instruccion
	int X = 1; // Donde se almacena el valor del registro, la posicion del
			   // sprite
	
	while(++ciclo) { // Nunca acaba
		
		if(contenido_en((ciclo-1)%40, X - 1, X + 1)){
			cout << "█";
		}
		else cout << '.';
		
		if(ciclo % 40 == 0) cout << endl;
		
		// Nos salimos si ya hemos dibujado todos los pixeles
		if (ciclo == 240) break;
		
		// Se carga la instruccion si  hace falta
		if(ciclos_restantes_instr <= 0) {
			arch_entrada >> ultima_instruccion;
			
			if(ultima_instruccion == "addx") {
				ciclos_restantes_instr = 2;
				arch_entrada >> val;
			}
			else if (ultima_instruccion == "noop") {
				ciclos_restantes_instr = 1;
			}
		}

		ciclos_restantes_instr--;
		
		// Se aplica la intruccion al fnal del ciclo
		if(ciclos_restantes_instr <= 0) {
			if(ultima_instruccion == "addx") {
				X += val;
			}
		}
	}
	
	return 0;
}


// != EFULGPAP







