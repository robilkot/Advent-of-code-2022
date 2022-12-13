#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
//#define PART1

using namespace std;

struct poshort {
	char z = 'a';
	short distance = 0;
	bool visited = 0;
};

short wavesearch(vector<vector<poshort>>& map, const short& begin_x, const short& begin_y, const short& end_x, const short& end_y) {
	map[begin_y][begin_x].visited = 1;
	queue<pair<short, short>> wave;
#ifdef PART1
	wave.push({ begin_x, begin_y });
#else
	wave.push({ end_x, end_y });
#endif

	for (; !wave.empty(); wave.pop()) {
		short x = wave.front().first, y = wave.front().second;

#ifndef PART1
		if (map[y][x].z == 'a') return map[y][x].distance;
#endif

		if (x > 0) {
#ifdef PART1
			if (!map[y][x - 1].visited && map[y][x - 1].z - map[y][x].z < 2) {
#else
			if (!map[y][x - 1].visited && map[y][x - 1].z - map[y][x].z > -2) {
#endif
				map[y][x - 1].distance = map[y][x].distance + 1;
				map[y][x - 1].visited = 1;
				wave.push({ x - 1, y });
			}
		}
		if (x < map[y].size() - 1) {
#ifdef PART1
			if (!map[y][x + 1].visited && map[y][x + 1].z - map[y][x].z < 2) {
#else
			if (!map[y][x + 1].visited && map[y][x + 1].z - map[y][x].z > -2) {
#endif
				map[y][x + 1].distance = map[y][x].distance + 1;
				map[y][x + 1].visited = 1;
				wave.push({ x + 1, y });
			}
		}
		if (y > 0) {
#ifdef PART1
			if (!map[y - 1][x].visited && map[y - 1][x].z - map[y][x].z < 2) {
#else
			if (!map[y - 1][x].visited && map[y - 1][x].z - map[y][x].z > -2) {
#endif
				map[y - 1][x].distance = map[y][x].distance + 1;
				map[y - 1][x].visited = 1;
				wave.push({ x, y - 1 });
			}
		}
		if (y < map.size() - 1) {
#ifdef PART1
			if (!map[y + 1][x].visited && map[y + 1][x].z - map[y][x].z < 2) {
#else
			if (!map[y + 1][x].visited && map[y + 1][x].z - map[y][x].z > -2) {
#endif
				map[y + 1][x].distance = map[y][x].distance + 1;
				map[y + 1][x].visited = 1;
				wave.push({ x, y + 1 });
			}
		}
	}
	return map[end_y][end_x].distance;
}

void day12() {
	ifstream inp("day12.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	short begin_x=0, begin_y=0, end_x=0, end_y=0, linenumber = 0;
	vector<vector<poshort>> map;
	for (string currentline; getline(inp, currentline); linenumber++) {
		if (currentline.empty()) continue;
		map.push_back({});
		for (short i = 0; i < currentline.size(); i++) {
			map[linenumber].push_back({ currentline[i] });
			if (currentline[i] == 'S') {
				map[linenumber][i].z = 'a';
				begin_x = i;
				begin_y = linenumber;
			}
			if (currentline[i] == 'E') {
				map[linenumber][i].z = 'z';
				end_x = i;
				end_y = linenumber;
			}
		}
	}

	cout << wavesearch(map, begin_x, begin_y, end_x, end_y) << "\n";
}
