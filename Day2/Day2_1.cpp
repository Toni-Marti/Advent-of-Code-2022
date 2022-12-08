/*
--- Day 2: Rock Paper Scissors ---

The Elves begin to set up camp on the beach. To decide whose tent gets to be 
closest to the snack storage, a giant Rock Paper Scissors tournament is already 
in progress.

Rock Paper Scissors is a game between two players. Each game contains many 
rounds; in each round, the players each simultaneously choose one of Rock, 
Paper, or Scissors using a hand shape. Then, a winner for that round is 
selected: Rock defeats Scissors, Scissors defeats Paper, and Paper defeats 
Rock. If both players choose the same shape, the round instead ends in a draw.

Appreciative of your help yesterday, one Elf gives you an encrypted strategy 
guide (your puzzle input) that they say will be sure to help you win. "The 
first column is what your opponent is going to play: A for Rock, B for Paper, 
and C for Scissors. The second column--" Suddenly, the Elf is called away to 
help with someone's tent.

The second column, you reason, must be what you should play in response: X for 
Rock, Y for Paper, and Z for Scissors. Winning every time would be suspicious, 
so the responses must have been carefully chosen.

The winner of the whole tournament is the player with the highest score. Your 
total score is the sum of your scores for each round. The score for a single 
round is the score for the shape you selected (1 for Rock, 2 for Paper, and 3 
for Scissors) plus the score for the outcome of the round (0 if you lost, 3 if 
the round was a draw, and 6 if you won).

Since you can't be sure if the Elf is trying to help you or trick you, you 
should calculate the score you would get if you were to follow the strategy 
guide.

For example, suppose you were given the following strategy guide:

A Y
B X
C Z

This strategy guide predicts and recommends the following:

    In the first round, your opponent will choose Rock (A), and you should 
    choose Paper (Y). This ends in a win for you with a score of 8 (2 because 
    you chose Paper + 6 because you won).
    In the second round, your opponent will choose Paper (B), and you should 
    choose Rock (X). This ends in a loss for you with a score of 1 (1 + 0).
    The third round is a draw with both players choosing Scissors, giving you a 
    score of 3 + 3 = 6.

In this example, if you were to follow the strategy guide, you would get a 
total score of 15 (8 + 1 + 6).

What would your total score be if everything goes exactly according to your 
strategy guide?
*/

// Compilar con:
// g++ Day2_1.cpp -o Day2_1.exe

using namespace std;

#include <iostream>
#include <fstream>
#include <map>

enum ROCK_PAP_SCIS {ROCK, PAPER, SCISSORS};
enum Result {LOSE, DRAW, WIN};

/**
 * @brief Imprime un mapa señalando a que valor apunta cada valor de llave
 */
template <typename llave, typename valor>
void ImprimeMap(const map<llave, valor> mapa) {
	typename map<llave, valor>::const_iterator it = mapa.begin();
	while(it != mapa.end()){
		cout << (*it).first << " -> " << (*it).second << endl;
		it++;
	}
}

Result Resultado(ROCK_PAP_SCIS mov_op, ROCK_PAP_SCIS mov_mio) {
	if(mov_op == mov_mio) {
		return DRAW;
	}
	
	bool pierdo = (mov_op == ROCK && mov_mio == SCISSORS) || 
				  (mov_op == PAPER && mov_mio == ROCK) ||
				  (mov_op == SCISSORS && mov_mio == PAPER);
				  
	if(pierdo) return LOSE;
	
	return WIN;
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
	
	int puntos = 0;
	char letra_op;
	char letra_mio;
	
	map<char, ROCK_PAP_SCIS> map_oponente;
	map_oponente.insert(pair('A', ROCK)); map_oponente.insert(pair('B', PAPER));
	map_oponente.insert(pair('C', SCISSORS));
	
	map<char, ROCK_PAP_SCIS> map_mio;
	map_mio.insert(pair('X', ROCK)); map_mio.insert(pair('Y', PAPER));
	map_mio.insert(pair('Z', SCISSORS));
	
	map<Result, int> map_puntos_LDW;
	map_puntos_LDW.insert(pair(LOSE, 0)); map_puntos_LDW.insert(pair(DRAW, 3));
	map_puntos_LDW.insert(pair(WIN, 6));
	
	map<ROCK_PAP_SCIS, int> map_puntos_RPS;
	map_puntos_RPS.insert(pair(ROCK, 1)); map_puntos_RPS.insert(pair(PAPER, 2));
	map_puntos_RPS.insert(pair(SCISSORS, 3));
	
//	ImprimeMap(map_oponente);
//	ImprimeMap(map_mio);
//	ImprimeMap(map_puntos_LDW);
//	ImprimeMap(map_puntos_RPS);
	
	while(true) {
		arch_entrada >> letra_op;
		arch_entrada >> letra_mio;
		if (arch_entrada.eof()) break;
		ROCK_PAP_SCIS mov_op = (*map_oponente.find(letra_op)).second;
		ROCK_PAP_SCIS mov_mio = (*map_mio.find(letra_mio)).second;
		int puntosRes = (*map_puntos_LDW.find(Resultado(mov_op, mov_mio))).second;
		int puntosMov = (*map_puntos_RPS.find(mov_mio)).second;
		puntos += puntosRes;
		puntos += puntosMov;
//		cout << letra_op << ' ' << letra_mio << "  Op: " << mov_op << " Mio: "
//			 << mov_mio << "  R:" << puntosRes << " M:" << puntosMov << endl; 
	}
	
	cout << "Puntos: " << puntos << endl;
	
	return puntos;
}
