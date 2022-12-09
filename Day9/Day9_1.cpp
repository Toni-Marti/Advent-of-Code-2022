/*
--- Day 9: Rope Bridge ---

This rope bridge creaks as you walk along it. You aren't sure how old it is, or
whether it can even support your weight.

It seems to support the Elves just fine, though. The bridge spans a gorge which
was carved out by the massive river far below you.

You step carefully; as you do, the ropes stretch and twist. You decide to
distract yourself by modeling rope physics; maybe you can even figure out where
not to step.

Consider a rope with a knot at each end; these knots mark the head and the tail
of the rope. If the head moves far enough away from the tail, the tail is
pulled toward the head.

Due to nebulous reasoning involving Planck lengths, you should be able to model
the positions of the knots on a two-dimensional grid. Then, by following a
hypothetical series of motions (your puzzle input) for the head, you can
determine how the tail will move.

Due to the aforementioned Planck lengths, the rope must be quite short; in
fact, the head (H) and tail (T) must always be touching (diagonally adjacent
and even overlapping both count as touching):

....
.TH.
....

....
.H..
..T.
....

...
.H. (H covers T)
...

If the head is ever two steps directly up, down, left, or right from the tail,
the tail must also move one step in that direction so it remains close enough:

.....    .....    .....
.TH.. -> .T.H. -> ..TH.
.....    .....    .....

...    ...    ...
.T.    .T.    ...
.H. -> ... -> .T.
...    .H.    .H.
...    ...    ...

Otherwise, if the head and tail aren't touching and aren't in the same row or
column, the tail always moves one step diagonally to keep up:

.....    .....    .....
.....    ..H..    ..H..
..H.. -> ..... -> ..T..
.T...    .T...    .....
.....    .....    .....

.....    .....    .....
.....    .....    .....
..H.. -> ...H. -> ..TH.
.T...    .T...    .....
.....    .....    .....

You just need to work out where the tail goes as the head follows a series of
motions. Assume the head and the tail both start at the same position,
overlapping.

For example:

R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2

This series of motions moves the head right four steps, then up four steps,
then left three steps, then down one step, and so on. After each step, you'll
need to update the position of the tail if the step means the head is no longer
adjacent to the tail. Visually, these motions occur as follows (s marks the
starting position as a reference point):

== Initial State ==

......
......
......
......
H.....  (H covers T, s)

== R 4 ==

......
......
......
......
TH....  (T covers s)

......
......
......
......
sTH...

......
......
......
......
s.TH..

......
......
......
......
s..TH.

== U 4 ==

......
......
......
....H.
s..T..

......
......
....H.
....T.
s.....

......
....H.
....T.
......
s.....

....H.
....T.
......
......
s.....

== L 3 ==

...H..
....T.
......
......
s.....

..HT..
......
......
......
s.....

.HT...
......
......
......
s.....

== D 1 ==

..T...
.H....
......
......
s.....

== R 4 ==

..T...
..H...
......
......
s.....

..T...
...H..
......
......
s.....

......
...TH.
......
......
s.....

......
....TH
......
......
s.....

== D 1 ==

......
....T.
.....H
......
s.....

== L 5 ==

......
....T.
....H.
......
s.....

......
....T.
...H..
......
s.....

......
......
..HT..
......
s.....

......
......
.HT...
......
s.....

......
......
HT....
......
s.....

== R 2 ==

......
......
.H....  (H covers T)
......
s.....

......
......
.TH...
......
s.....

After simulating the rope, you can count up all of the positions the tail
visited at least once. In this diagram, s again marks the starting position
(which the tail also visited) and # marks other positions the tail visited:

..##..
...##.
.####.
....#.
s###..

So, there are 13 positions the tail visited at least once.

Simulate your complete hypothetical series of motions. How many positions does
the tail of the rope visit at least once?

*/

// Compilar con:
// g++ Day9_1.cpp -o Day9_1.bin

#include <iostream>
#include <fstream>
#include <set>
#include <stdlib.h>
#include <string>

using namespace std;

struct vec2d {
	int x = 0, y = 0;

	vec2d(int x=0, int y=0) {
		this->x = x;
		this->y = y;
	}

	vec2d operator+(const vec2d &other) const{
		vec2d suma = *this;
		suma += other;
		return suma;
	}

	vec2d &operator+=(const vec2d &other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	vec2d operator-() const{
		return vec2d(-x, -y);
	}

	vec2d operator-(const vec2d &other) const{
		vec2d suma = *this;
		suma += -other;
		return suma;
	}

	vec2d &operator-=(const vec2d &other) {
		*this += -other;
		return *this;
	}

	bool operator==(const vec2d &other) const{
		return x == other.x && y == other.y;
	}
	
	string toString() {
		return to_string(x) + "," + to_string(y);
	}
};

void mueve(vec2d& pos, char dir) {
	switch(dir) {
	case 'U':
		pos += vec2d(0, 1);
		break;
	case 'R':
		pos += vec2d(1, 0);
		break;
	case 'D':
		pos += vec2d(0, -1);
		break;
	case 'L':
		pos += vec2d(-1, 0);
		break;
	}
}

int clamp (int val, int min = -1, int max = 1) {
	if(val >= max) return max;
	if(val <= min) return min;
	return val;
}

void ActualizaTail(vec2d& tail, const vec2d& head) {
	vec2d direccion = head - tail;
	bool seMueve = abs(direccion.x) == 2 || abs(direccion.y) == 2;

	if(!seMueve) return;

	direccion.x = clamp(direccion.x);
	direccion.y = clamp(direccion.y);

	tail += direccion;
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

	vec2d H_pos, T_pos;
	set<string> recorrido;
	recorrido.insert(H_pos.toString());

	char direccion;
	int veces;
	
	int linea = 1;
	
	while(!arch_entrada.eof()) {
		arch_entrada >> direccion;
		arch_entrada >> veces;
		
		if(arch_entrada.eof()) break;
		
		for(int i=0; i<veces; i++) {
			mueve(H_pos, direccion);
			ActualizaTail(T_pos, H_pos);
			recorrido.insert(T_pos.toString());
		}
		
		cout << linea++ << endl;
	}

	cout << "SOLUCION: " << recorrido.size() << endl;

	return recorrido.size();
}

// < 6596
// != 3589
// != 6360
// > 3994



