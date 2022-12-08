/*
--- Day 7: No Space Left On Device ---

You can hear birds chirping and raindrops hitting leaves as the expedition 
proceeds. Occasionally, you can even hear much louder sounds in the distance; 
how big do the animals get out here, anyway?

The device the Elves gave you has problems with more than just its 
communication system. You try to run a system update:

$ system-update --please --pretty-please-with-sugar-on-top
Error: No space left on device

Perhaps you can delete some files to make space for the update?

You browse around the filesystem to assess the situation and save the resulting 
terminal output (your puzzle input). For example:

$ cd /
$ ls
dir a
14848514 b.txt
8504156 c.dat
dir d
$ cd a
$ ls
dir e
29116 f
2557 g
62596 h.lst
$ cd e
$ ls
584 i
$ cd ..
$ cd ..
$ cd d
$ ls
4060174 j
8033020 d.log
5626152 d.ext
7214296 k

The filesystem consists of a tree of files (plain data) and directories (which 
can contain other directories or files). The outermost directory is called /. 
You can navigate around the filesystem, moving into or out of directories and 
listing the contents of the directory you're currently in.

Within the terminal output, lines that begin with $ are commands you executed, 
very much like some modern computers:

    cd means change directory. This changes which directory is the current 
    directory, but the specific result depends on the argument:
        cd x moves in one level: it looks in the current directory for the 
        directory named x and makes it the current directory.
        cd .. moves out one level: it finds the directory that contains the 
        current directory, then makes that directory the current directory.
        cd / switches the current directory to the outermost directory, /.
    ls means list. It prints out all of the files and directories immediately 
    contained by the current directory:
        123 abc means that the current directory contains a file named abc with 
        size 123.
        dir xyz means that the current directory contains a directory named xyz.

Given the commands and output in the example above, you can determine that the 
filesystem looks visually like this:

- / (dir)
  - a (dir)
    - e (dir)
      - i (file, size=584)
    - f (file, size=29116)
    - g (file, size=2557)
    - h.lst (file, size=62596)
  - b.txt (file, size=14848514)
  - c.dat (file, size=8504156)
  - d (dir)
    - j (file, size=4060174)
    - d.log (file, size=8033020)
    - d.ext (file, size=5626152)
    - k (file, size=7214296)

Here, there are four directories: / (the outermost directory), a and d (which 
are in /), and e (which is in a). These directories also contain files of 
various sizes.

Since the disk is full, your first step should probably be to find directories 
that are good candidates for deletion. To do this, you need to determine the 
total size of each directory. The total size of a directory is the sum of the 
sizes of the files it contains, directly or indirectly. (Directories themselves 
do not count as having any intrinsic size.)

The total sizes of the directories above can be found as follows:

    The total size of directory e is 584 because it contains a single file i of 
    size 584 and no other directories.
    The directory a has total size 94853 because it contains files f (size 
    29116), g (size 2557), and h.lst (size 62596), plus file i indirectly (a 
    contains e which contains i).
    Directory d has total size 24933642.
    As the outermost directory, / contains every file. Its total size is 
    48381165, the sum of the size of every file.

To begin, find all of the directories with a total size of at most 100000, 
then calculate the sum of their total sizes. In the example above, these 
directories are a and e; the sum of their total sizes is 95437 (94853 + 584). 
(As in this example, this process can count files more than once!)

Find all of the directories with a total size of at most 100000. What is the 
sum of the total sizes of those directories?

Your puzzle answer was 1845346.
--- Part Two ---

Now, you're ready to choose a directory to delete.

The total disk space available to the filesystem is 70000000. To run the 
update, you need unused space of at least 30000000. You need to find a 
directory you can delete that will free up enough space to run the update.

In the example above, the total size of the outermost directory (and thus the 
total amount of used space) is 48381165; this means that the size of the unused 
space must currently be 21618835, which isn't quite the 30000000 required by 
the update. Therefore, the update still requires a directory with total size of 
at least 8381165 to be deleted before it can run.

To achieve this, you have the following options:

    Delete directory e, which would increase unused space by 584.
    Delete directory a, which would increase unused space by 94853.
    Delete directory d, which would increase unused space by 24933642.
    Delete directory /, which would increase unused space by 48381165.

Directories e and a are both too small; deleting them would not free up enough 
space. However, directories d and / are both big enough! Between these, choose 
the smallest: d, increasing unused space by 24933642.

Find the smallest directory that, if deleted, would free up enough space on the 
filesystem to run the update. What is the total size of that directory?

Your puzzle answer was 3636703.

Both parts of this puzzle are complete! They provide two gold stars: **
*/

// Compilar con:
// g++ Day7.cpp -o Day7.bin

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>   
#include <vector>

using namespace std;

enum tipoArch {
	ARCHIVO, DIR
};

class archivo {
private:
	string nombre;
	tipoArch tipo;
	archivo *padre_ptr;
	int tamanyo;
	vector<archivo> hijos;
	
	void imprime(int profundidad) {
		for(int i=0; i<profundidad; i++) {
			cout << "|" <<'\t';
		}
		cout << nombre;
		if(tipo == DIR) cout << " (dir)" << endl;
		else cout << " " << tamanyo << endl;
		
		for(archivo &hijo : hijos) {
			hijo.imprime(profundidad+1);
		}
	}
	
	void sumaDirMenoresOIgualesA(const int TAM_LIMITE, int &tam_actual) {
		if(tipo == DIR && getTamanyo() <= TAM_LIMITE) tam_actual += getTamanyo();
		
		for(archivo hijo : hijos) {
			hijo.sumaDirMenoresOIgualesA(TAM_LIMITE, tam_actual);
		}
	}
	
	void smallesBiggerOrEqualThan(const int TAM_LIMITE, bool hay_uno, int &solucion) {
		if(tipo == DIR && getTamanyo() >= TAM_LIMITE &&
		  ((getTamanyo() < solucion) || (!hay_uno))) {
			hay_uno = true;
			solucion = getTamanyo();
		}
		
		for(archivo hijo : hijos) {
			hijo.smallesBiggerOrEqualThan(TAM_LIMITE, hay_uno, solucion);
		}
	}

public:
	archivo(string nombre, tipoArch tipo, archivo* padre_ptr = nullptr, int tamanyo = 0) {
		this->nombre = nombre;
		this->tipo = tipo;
		this->padre_ptr = padre_ptr;
		this->tamanyo = tamanyo;
	}
	
	string getRuta() const {
		if(padre_ptr == nullptr) {
			return nombre;
		}
		
		string rutaPadre = padre_ptr->getRuta();
		
		if(rutaPadre[rutaPadre.length() - 1] == '/') {
			return rutaPadre + nombre;
		}
		
		return rutaPadre + "/" + nombre;
	}
	
	string getNombre() {
		return nombre;
	}
	
	tipoArch getTipo() {
		return tipo;
	}
	
	archivo *getPadrePtr() {
		return padre_ptr;
	}
	
	int getTamanyo() {
		if(tipo == ARCHIVO) {
			return tamanyo;
		}
		else {
			int tam_dir = 0;
			for(archivo &hijo : hijos) {
				tam_dir += hijo.getTamanyo();
			}
			return tam_dir;
		}
	}
	
	
	vector<archivo> getHijosPtrs() {
		return hijos;
	}
	
	// Devuelve el mismo abjeto si el hijo no existe
	archivo &getHijo(string nombre) {
		for(archivo &hijo : hijos) {
			if (nombre == hijo.getNombre()) return hijo;
		}
		return *this;
	}
	
	int getNumHijos() {
		return hijos.size();
	}
	
	bool tieneHijo(string nombre) {
		if(getHijo(nombre) != *this) return true;
		return false;
	}
	
	bool AnyadeHijo(string nombre, tipoArch tipo, int tamanyo = 0) {
		if(tieneHijo(nombre)) return false;
		
		hijos.push_back(archivo(nombre, tipo, this, tamanyo));
		return true;
	}
	
	bool operator==(archivo &otro) {
		return otro.getRuta() == getRuta();
	}
	
	bool operator!=(archivo &otro) {
		return !(otro.getRuta() == getRuta());
	}
	
	void imprime() { imprime(0); }
	
	int sumaDirMenoresOIgualesA(const int TAM_LIMITE) {
		int solucion = 0;
		if(tipo == DIR && getTamanyo() <= TAM_LIMITE) solucion += getTamanyo();
		
		for(archivo hijo : hijos) {
			hijo.sumaDirMenoresOIgualesA(TAM_LIMITE, solucion);
		}
		
		return solucion;
	}
	
	int smallesBiggerOrEqualThan(const int TAM_LIMITE) {
		bool hay_uno = false;
		int solucion = -1;
		if(tipo == DIR && getTamanyo() >= TAM_LIMITE &&
		  ((getTamanyo() < solucion) || (!hay_uno))) {
			hay_uno = true;
			solucion = getTamanyo();
		}
		
		for(archivo hijo : hijos) {
			hijo.smallesBiggerOrEqualThan(TAM_LIMITE, hay_uno, solucion);
		}
		
		return solucion;
	}
};

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
	
	// Metemos todos los archivos en un arbol
	string basura;
	getline(arch_entrada, basura);
	
	archivo directrio_raiz("/", DIR);
	archivo *dir_actual_ptr = &directrio_raiz;
	int linea = 2;
	
	while(true) {
		
		string linea_actual;
		getline(arch_entrada, linea_actual);
		if(arch_entrada.eof()) break; // NOS SALIMOS AQUI
		
		cout << linea++ << ". " << linea_actual << endl;
		istringstream linea_actual_in(linea_actual);
		string parte1;
		string parte2;
		string parte3 = "";
		
		linea_actual_in >> parte1;
		
		if(parte1 == "$") { // Si la linea actual es una orden
			linea_actual_in >> parte2;
			
			if(parte2 == "ls") continue; // Si es un ls ignoramos la orden
			else linea_actual_in >> parte3; // Si es cd actualizamos el dir_actual_ptr
			
			if(parte3 == "..") {
				dir_actual_ptr = dir_actual_ptr->getPadrePtr();
			}
			else if (dir_actual_ptr->getHijo(parte3) != *dir_actual_ptr) {
				dir_actual_ptr = &dir_actual_ptr->getHijo(parte3);
			}
			else {
				dir_actual_ptr->AnyadeHijo(parte3, DIR);
				dir_actual_ptr = &dir_actual_ptr->getHijo(parte3);
			}
		}
		else {
			linea_actual_in >> parte2;
			
			if(parte1 == "dir") {
				dir_actual_ptr->AnyadeHijo(parte2, DIR);
			}
			else {
				int tam_arch = stoi(parte1);
				dir_actual_ptr->AnyadeHijo(parte2, ARCHIVO, tam_arch);
			}
		}
	}
	
	cout << endl;
	directrio_raiz.imprime();
	cout << endl;
	
	const int TAM_LIMITE1 = 100000;
	cout << "Solucion 1: " << directrio_raiz.sumaDirMenoresOIgualesA(TAM_LIMITE1)
		 << endl;
	
	const int TOTAL = 70000000;
	const int NECESARIO = 30000000;
	const int USADO = directrio_raiz.getTamanyo();
	const int SIN_USAR = TOTAL - USADO;
	const int A_LIBERAR = NECESARIO - SIN_USAR;
	
	// es < 8739730
	cout << "Solucion 2: " << directrio_raiz.smallesBiggerOrEqualThan(A_LIBERAR)
		 << endl;
	
	return 0;
}




