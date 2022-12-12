/*
--- Part Two ---

As you walk up the hill, you suspect that the Elves will want to turn this into 
a hiking trail. The beginning isn't very scenic, though; perhaps you can find a 
better starting point.

To maximize exercise while hiking, the trail should start as low as possible:
 elevation a. The goal is still the square marked E. However, the trail should 
 still be direct, taking the fewest steps to reach its goal. So, you'll need to 
 find the shortest path from any square at elevation a to the square marked E.

Again consider the example from above:

Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi

Now, there are six choices for starting position (five marked a, plus the 
square marked S that counts as being at elevation a). If you start at the 
bottom-left square, you can reach the goal most quickly:

...v<<<<
...vv<<^
...v>E^^
.>v>>>^^
>^>>>>>^

This path reaches the goal in only 29 steps, the fewest possible.

What is the fewest steps required to move starting from any square with 
elevation a to the location that should get the best signal?
*/

// Compilar con:
// g++ Day12_2.cpp -o Day12_2.bin

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char STARTING_CHAR = 'S';
const char ENDING_CHAR = 'E';
int min_steps_fom_a = 380; // initialized at previous answer

struct vec2d {
	int x = 0;
	int y = 0;
	
	vec2d(int x_ini, int y_ini) {
		x = x_ini;
		y = y_ini;
	}
};

vector<vec2d> cardinal_directions;

int heigth(char car) {
	if(car >= 'a' && car <= 'z') return car - 'a';
	else if (car == STARTING_CHAR) return  heigth('a');
	else if (car == ENDING_CHAR) return  heigth('z');
	else {
		cerr << car <<  " -> Invalid character (in function height)" << endl;
		exit(-1);
	}
}

bool reachedEnd(const vector<vec2d> &positions,
				const vector<vector<char>> &map) {
	for(const vec2d &pos : positions) {
		if(map[pos.x][pos.y] == ENDING_CHAR) return true;
	}
	
	return false;
}

bool shouldGo(const vec2d &from, const vec2d &candidate,
			  const vector<vector<char>> &map, 
			  const vector<vector<bool>> &visited) {
	
	// Dont go if it's out of bounds
	if(candidate.x < 0 || candidate.y < 0 ||
	   candidate.x >= map.size() || candidate.y >= map[candidate.x].size()) {
		return false;
	}
	
	// Dont go if it has already been visited
	if(visited[candidate.x][candidate.y]) {
		return false;
	}
	
	// Dont go if the heigth isn't right
	if(heigth(map[from.x][from.y]) + 1 < heigth(map[candidate.x][candidate.y])
	   && heigth(map[candidate.x][candidate.y]) != heigth('a'))
		return false;
	
	// Otherwise it should go there
	return true;
}

int solve(const vec2d &start_pos, const vector<vector<char>> &map) {
	
	int steps = 0;
	
	vector<vector<bool>> visited(map.size(), 
								 vector<bool>(map[0].size(), false));
	vector<vec2d> visiting;
	visiting.push_back(start_pos);
	vector<vec2d> new_places;
	
	while(!reachedEnd(visiting, map) && !visiting.empty() && steps < min_steps_fom_a) {
		for(const vec2d &pos : visiting) {
			for(const vec2d &direction : cardinal_directions) {
				vec2d candidate(pos.x + direction.x, pos.y + direction.y);
				
				if(shouldGo(pos, candidate, map, visited)) {
					new_places.push_back(candidate);
					visited[candidate.x][candidate.y] = true;
				}
			}
		}
		
		visiting = new_places;
		steps++;
	}
	
	if(visiting.empty()) return -1;
	else return steps;
}

vec2d find(char car, vector<vector<char>> map) {
	for(int row=0; row<map.size(); row++){
		for(int column=0; column<map[row].size(); column++) {
			if(map[row][column] == car) return vec2d(row, column);
		}
	}
	
	cerr << car << " -> character not found (in function find)" << endl;
	exit(-1);
}

int main(int argc, char *argv[]){
	cardinal_directions.push_back(vec2d(0, 1));
	cardinal_directions.push_back(vec2d(1, 0));
	cardinal_directions.push_back(vec2d(0, -1));
	cardinal_directions.push_back(vec2d(-1, 0));
	
	ifstream input_file;
	string file_path = "Entrada.txt";
	
	if(argc > 2) {
		cerr << "ERROR: Demasiados argumentos." << endl;
		return -1;
	}
	else if( argc == 2) {
		file_path = argv[1];
	}
	
	input_file.open(file_path);
	
	if(!input_file.is_open()) {
		cerr << "ERROR: No se pudo abrir el archivo: " << file_path << endl;
		return -2;
	}
	
	vector<vector<char>> map;
	
	while(true) {
		string row_str;
		getline(input_file, row_str);
		
		// We exit if the row is empty() (end of matrix reached)
		if(row_str.size() == 0) break;
		
		vector<char> row_vec;
		for(string::const_iterator it = row_str.begin(); it != row_str.end();
			it++) {
			row_vec.push_back(*it);
		}
		map.push_back(row_vec);
	}
	
	vec2d start_coords = find(STARTING_CHAR, map);
	vector<vector<bool>> visited(map.size(), 
								 vector<bool>(map[0].size(), false));
	
	for(int row=0; row<map.size(); row++){
		for(int column=0; column<map[row].size(); column++) {
			if(heigth(map[row][column]) == heigth('a')) {
				int current_solution = solve(vec2d(row, column), map);
				cout << current_solution << "  ";
				if(current_solution != -1) {
					min_steps_fom_a = min(min_steps_fom_a, current_solution);
				}
				cout << row << " " << column << "   ";
			}
			cout << endl;
		}
	}
	
	cout << "Steps: " << min_steps_fom_a << endl;
	
	return 0;
}










