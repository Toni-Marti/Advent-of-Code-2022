/*
STATEMENT
*/

// Compile with:
// g++ DayX_1.cpp -o DayX_1.bin

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
	ifstream input_file;
	string file_path = "Input.txt";
	
	if(argc > 2) {
		cerr << "ERROR: Too many arguments." << endl;
		return -1;
	}
	else if( argc == 2) {
		file_path = argv[1];
	}
	
	input_file.open(file_path);
	
	if(!input_file.is_open()) {
		cerr << "ERROR: Coudn't open the file: " << file_path << endl;
		return -2;
	}
	
	
	return 0;
}










