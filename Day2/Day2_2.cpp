/*
--- Part Two ---

The Elf finishes helping with the tent and sneaks back over to you. "Anyway, 
the second column says how the round needs to end: X means you need to lose, Y 
means you need to end the round in a draw, and Z means you need to win. Good 
luck!"

The total score is still calculated in the same way, but now you need to figure 
out what shape to choose so the round ends as indicated. The example above now 
goes like this:

    In the first round, your opponent will choose Rock (A), and you need the 
    round to end in a draw (Y), so you also choose Rock. This gives you a score 
    of 1 + 3 = 4.
    In the second round, your opponent will choose Paper (B), and you choose 
    Rock so you lose (X) with a score of 1 + 0 = 1.
    In the third round, you will defeat your opponent's Scissors with Rock for a 
    score of 1 + 6 = 7.

Now that you're correctly decrypting the ultra top secret strategy guide, you 
would get a total score of 12.

Following the Elf's instructions for the second column, what would your total 
score be if everything goes exactly according to your strategy guide?
*/

// Compilar con:
// g++ Day2_2.cpp -o Day2_2.exe

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

ROCK_PAP_SCIS MiMov(ROCK_PAP_SCIS mov_op, Result resultado) {
	if(resultado == DRAW) return mov_op;
	
	if(resultado == LOSE) {
		if(mov_op == ROCK){
			return SCISSORS;
		}
		else if(mov_op == PAPER){
			return ROCK;
		}
		else { // SCISSORS
			return PAPER;
		}
	}
	
	// Seguro que  resultado == WIN
	if(mov_op == ROCK){
		return PAPER;
	}
	else if(mov_op == PAPER){
		return SCISSORS;
	}
	else { // SCISSORS
		return ROCK;
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
	
	int puntos = 0;
	char letra_op;
	char letra_mio;
	
	map<char, ROCK_PAP_SCIS> map_oponente;
	map_oponente.insert(pair('A', ROCK)); map_oponente.insert(pair('B', PAPER));
	map_oponente.insert(pair('C', SCISSORS));
	
	map<char, Result> map_mio;
	map_mio.insert(pair('X', LOSE)); map_mio.insert(pair('Y', DRAW));
	map_mio.insert(pair('Z', WIN));
	
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
		Result resultado = (*map_mio.find(letra_mio)).second;
		int puntosRes = (*map_puntos_LDW.find(resultado)).second;
		int puntosMov = (*map_puntos_RPS.find(MiMov(mov_op, resultado))).second;
		puntos += puntosRes;
		puntos += puntosMov;
//		cout << letra_op << ' ' << letra_mio << "  Op: " << mov_op << " Mio: "
//			 << mov_mio << "  R:" << puntosRes << " M:" << puntosMov << endl; 
	}
	
	cout << "Puntos: " << puntos << endl;
	
	return puntos;
}
