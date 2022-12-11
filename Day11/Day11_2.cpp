/*
--- Part Two ---

You're worried you might not ever get your items back. So worried, in fact, 
that your relief that a monkey's inspection didn't damage an item no longer 
causes your worry level to be divided by three.

Unfortunately, that relief was all that was keeping your worry levels from 
eaching ridiculous levels. You'll need to find another way to keep your worry 
levels manageable.

At this rate, you might be putting up with these monkeys for a very long time - 
possibly 10000 rounds!

With these new rules, you can still figure out the monkey business after 10000 
rounds. Using the same example above:

== After round 1 ==
Monkey 0 inspected items 2 times.
Monkey 1 inspected items 4 times.
Monkey 2 inspected items 3 times.
Monkey 3 inspected items 6 times.

== After round 20 ==
Monkey 0 inspected items 99 times.
Monkey 1 inspected items 97 times.
Monkey 2 inspected items 8 times.
Monkey 3 inspected items 103 times.

== After round 1000 ==
Monkey 0 inspected items 5204 times.
Monkey 1 inspected items 4792 times.
Monkey 2 inspected items 199 times.
Monkey 3 inspected items 5192 times.

== After round 2000 ==
Monkey 0 inspected items 10419 times.
Monkey 1 inspected items 9577 times.
Monkey 2 inspected items 392 times.
Monkey 3 inspected items 10391 times.

== After round 3000 ==
Monkey 0 inspected items 15638 times.
Monkey 1 inspected items 14358 times.
Monkey 2 inspected items 587 times.
Monkey 3 inspected items 15593 times.

== After round 4000 ==
Monkey 0 inspected items 20858 times.
Monkey 1 inspected items 19138 times.
Monkey 2 inspected items 780 times.
Monkey 3 inspected items 20797 times.

== After round 5000 ==
Monkey 0 inspected items 26075 times.
Monkey 1 inspected items 23921 times.
Monkey 2 inspected items 974 times.
Monkey 3 inspected items 26000 times.

== After round 6000 ==
Monkey 0 inspected items 31294 times.
Monkey 1 inspected items 28702 times.
Monkey 2 inspected items 1165 times.
Monkey 3 inspected items 31204 times.

== After round 7000 ==
Monkey 0 inspected items 36508 times.
Monkey 1 inspected items 33488 times.
Monkey 2 inspected items 1360 times.
Monkey 3 inspected items 36400 times.

== After round 8000 ==
Monkey 0 inspected items 41728 times.
Monkey 1 inspected items 38268 times.
Monkey 2 inspected items 1553 times.
Monkey 3 inspected items 41606 times.

== After round 9000 ==
Monkey 0 inspected items 46945 times.
Monkey 1 inspected items 43051 times.
Monkey 2 inspected items 1746 times.
Monkey 3 inspected items 46807 times.

== After round 10000 ==
Monkey 0 inspected items 52166 times.
Monkey 1 inspected items 47830 times.
Monkey 2 inspected items 1938 times.
Monkey 3 inspected items 52013 times.

After 10000 rounds, the two most active monkeys inspected items 52166 and 52013 
times. Multiplying these together, the level of monkey business in this 
situation is now 2713310158.

Worry levels are no longer divided by three after each item is inspected; 
you'll need to find another way to keep your worry levels manageable. Starting 
again from the initial state in your puzzle input, what is the level of monkey 
business after 10000 rounds?
*/

// Compilar con:
// g++ Day11_2.cpp -o Day11_2.bin

#include <iostream>
#include <fstream>
#include <list>
#include <sstream>

using namespace std;

typedef list<long> lista_items;

long convierteArgumento(string arg, long old_val) {
	if(arg == "old") return old_val;
	else return stoi(arg);
}

long MCD(long a, long b) {
	if (b == 0)	return a;
	return MCD(b, a % b);
}

long MCM(long a, long b) {
	return (a*b)/MCD(a, b);
}

class Monkey {
private:
	static list<Monkey> monos;
	static long mcm_divisores; // Ha de actualizarse cada vez que se mete 
	lista_items items;
	char operation;
	pair<string,string> operands;
	int divisible_by;
	int monkey_true, monkey_false;
	long num_inspections = 0;
	
	void pasa_a_mono(int n) {
		list<Monkey>::iterator it = Monkey::getMonos().begin(); 
		for(int num_mono = 0; num_mono < n; num_mono++) {
			it++;
		}
		(*it).items.push_back(this->items.front());
		this->items.pop_front();
	}
	
	void inspecciona() {
		pair<long,long> arguments;
		arguments.first = convierteArgumento(operands.first, items.front());
		arguments.second = convierteArgumento(operands.second, items.front());
		long result;
		switch (operation) {
		case '+':
			result = arguments.first + arguments.second;
			break;
		case '*':
			result = arguments.first * arguments.second;
			break;
		}
		items.front() = result;
		num_inspections++;
	}
	
public:
	static list<Monkey> &getMonos() {
		return monos;
	}
	
	static void actualizaMCM(int num) {
		// Bastaba multiplicar, ya que todos los num son primos
		mcm_divisores = MCM(mcm_divisores, num);
	}
	
	static long getDivisoresMCM() {
		return mcm_divisores;
	}
	
	long getInspecciones() const {
		return num_inspections;
	}
	
	void hazTurno() {
		int num_items = items.size();
		for(int i = 0; i<num_items; i++) {
			inspecciona();
			items.front() %= Monkey::getDivisoresMCM();
			if(items.front() % divisible_by == 0) pasa_a_mono(monkey_true);
			else pasa_a_mono(monkey_false);
		}
	}
	
	bool operator<(Monkey &other) {
		return num_inspections < other.num_inspections;
	}
	
	/**
	 * @pre El mono tiene al menos un item
	 * @post Se anuyade un mono a la lista de monos
	 */ 
	friend istream & operator>>(istream &in, Monkey &this_ape) {
		// Primera y sugunda linea
		string _ = "";
		while( _ != "items:") in >> _ ;
		string linea_items;
		getline(in, linea_items);
		istringstream flujo_itmes(linea_items);
		while(!flujo_itmes.eof()) {
			string item;
			flujo_itmes >> item;
			this_ape.items.push_back(stoi(item));
		}
		
		// Tercera linea
		while( _ != "=") in >> _ ;
		in >> this_ape.operands.first >> this_ape.operation
		   >> this_ape.operands.second;
		
		// Cuarta linea
		while( _ != "by") in >> _ ;
		in >> this_ape.divisible_by;
		
		// Quinta linea
		while( _ != "monkey") in >> _ ;
		in >> this_ape.monkey_true;
		
		// Sexta linea
		in >> _;
		while( _ != "monkey") in >> _ ;
		in >> this_ape.monkey_false;
		
		Monkey::getMonos().push_back(this_ape);
		Monkey::actualizaMCM(this_ape.divisible_by);
		return in;
	}
	
	// For debugging
	friend ostream & operator<<(ostream &out, const Monkey &this_ape) {
		// Linea uno
		out << "Items:";
		for(long item : this_ape.items) {
			out << " " << item;
		}
		out << endl;
		
		// Linea dos
		out << "Operation: " << this_ape.operands.first << " " 
			<< this_ape.operation << " " << this_ape.operands.second << endl;
		
		// Linea tres
		out << "Pasa al mono " << this_ape.monkey_true << " si el item es"
			<< " divisible entre " << this_ape.divisible_by << ", si no, pasa"
			<< " al " << this_ape.monkey_false << endl;
		
		return out;
	}
};

list<Monkey> Monkey::monos;
long Monkey::mcm_divisores = 1;

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
	
	while(!arch_entrada.eof()) {
		Monkey registrar_mono;
		arch_entrada >> registrar_mono;
		cout << registrar_mono << endl;
		
		string _;
		arch_entrada >> _; 
	}
	
	const int RONDAS = 10000;
	
	for(int i=0; i<RONDAS; i++) {
		for(Monkey &mono : Monkey::getMonos()) {
			mono.hazTurno();
		}
	}
	
	list<Monkey> ordenada = Monkey::getMonos();
	ordenada.sort();
	ordenada.reverse();
	
	for(Monkey mono : ordenada) {
		cout << "Numero inspecciones: " << mono.getInspecciones() << endl;
	}
	cout << endl;
	
	for(Monkey mono : ordenada) {
		cout << mono << endl;
	}
	cout << endl;
	
	long resultado = 1;
	list<Monkey>::iterator it = ordenada.begin();
	
	// Se multiplican los 2 mas grandes
	for(int i=0; i<2; i++) {
		resultado *= (*it).getInspecciones();
		it++;
	}
	
	cout << "Resultado: " << resultado << endl;
	
	return resultado;
}








