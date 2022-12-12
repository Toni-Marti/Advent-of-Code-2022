/*
--- Day 12: Hill Climbing Algorithm ---

You try contacting the Elves using your handheld device, but the river you're 
following must be too low to get a decent signal.

You ask the device for a heightmap of the surrounding area (your puzzle input). 
The heightmap shows the local area from above broken into a grid; the elevation 
of each square of the grid is given by a single lowercase letter, where a is 
the lowest elevation, b is the next-lowest, and so on up to the highest 
levation, z.

Also included on the heightmap are marks for your current position (S) and the 
location that should get the best signal (E). Your current position (S) has 
elevation a, and the location that should get the best signal (E) has elevation 
z.

You'd like to reach E, but to save energy, you should do it in as few steps as 
possible. During each step, you can move exactly one square up, down, left, or 
right. To avoid needing to get out your climbing gear, the elevation of the 
destination square can be at most one higher than the elevation of your current 
square; that is, if your current elevation is m, you could step to elevation n, 
but not to elevation o. (This also means that the elevation of the destination 
square can be much lower than the elevation of your current square.)

For example:

Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi

Here, you start in the top-left corner; your goal is near the middle. You could 
start by moving down or right, but eventually you'll need to head toward the e 
at the bottom. From there, you can spiral around to the goal:

v..v<<<<
>v.vv<<^
.>vv>E^^
..v>>>^^
..>>>>>^

In the above diagram, the symbols indicate whether the path exits each square 
moving up (^), down (v), left (<), or right (>). The location that should get 
the best signal is still E, and . marks unvisited squares.

This path reaches the goal in 31 steps, the fewest possible.

What is the fewest steps required to move from your current position to the 
location that should get the best signal?
*/

// Compilar con:
// g++ Day12_1.cpp -o Day12_1.bin

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const char STARTING_CHAR = 'S';
const char ENDING_CHAR = 'E';

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
	if(visited[candidate.x][candidate.y]) return false;
	
	// Dont go if the height isn't right
	if(heigth(map[from.x][from.y]) + 1 < heigth(map[candidate.x][candidate.y]))
		return false;
	
	// Otherwise it should go there
	return true;
}

int solve(const vec2d &start_pos, const vector<vector<char>> &map, 
		  vector<vector<bool>> &visited) {
	
	int steps = 0;
	vector<vec2d> visiting;
	visiting.push_back(start_pos);
	vector<vec2d> new_places;
	
	while(!reachedEnd(visiting, map)) {
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
	
	return steps;
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
	
	cout << "Steps: " << solve(start_coords, map, visited) << endl;
	
	return 0;
}










