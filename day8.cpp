#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

template < typename T >
void showmap(vector<vector< T >> map) {
	for (int i = 0; i < map.size(); i++) {
		for (int k = 0; k < map[i].size(); k++) cout << map[i][k] << " ";
		cout << "\n";
	}
	cout << "\n";
}

void check(const vector<vector<int>>& map, vector<vector<bool>>& visible) {
	for (int i = 0; i < map.size(); i++) {
		visible[i][0] = 1;
		visible[i][visible.size()-1] = 1;

		int max = map[i][0]; // left-to-right
		for (int k = 1; k < map[i].size()-1; k++) {
			if (map[i][k] > max) {
				max = map[i][k];
				visible[i][k] = 1;
			}
		}

		max = map[i][map.size()-1]; // right-to-left
		for (int k = map[i].size() - 2; k > 0; k--) {
			if (map[i][k] > max) {
				max = map[i][k];
				visible[i][k] = 1;
			}
		}
	}
}

template < typename T >
void rotatematrix(vector<vector< T >>& mat) {
	if (mat.size() != mat[0].size()) return;
	int N = mat.size();
	for (int x = 0; x < N / 2; x++) {
		for (int y = x; y < N - x - 1; y++) {
			T temp = mat[x][y];
			mat[x][y] = mat[y][N - 1 - x];
			mat[y][N - 1 - x] = mat[N - 1 - x][N - 1 - y];
			mat[N - 1 - x][N - 1 - y] = mat[N - 1 - y][x];
			mat[N - 1 - y][x] = temp;
		}
	}
}

void day8_1() {
	ifstream inp("day8.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}
	vector<vector<int>> map;
	string currentstring;
	for (int linenumber = 0; getline(inp, currentstring); linenumber++) {
		map.push_back({});
		for (char x : currentstring) map[linenumber].push_back(x - 48);
	}
	inp.close();

	vector<vector<bool>> visible;
	for (int i = 0; i < map.size(); i++) {
		visible.push_back({});
		for (int k = 0; k < map[i].size(); k++) visible[i].push_back(0);
	}

	check(map, visible);
	rotatematrix(map);
	rotatematrix(visible);
	check(map, visible);
	
	int answer = 0;
	for (vector<bool> i : visible) for (bool k : i) answer += k;

	cout << "Visible trees: " << answer << "\n";
}