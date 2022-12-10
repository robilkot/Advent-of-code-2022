#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <set>
#include <vector>

using namespace std;

void calc_tpos(vector<pair<int, int>>& knots, const char& dir) {
	switch (dir) {
	case 'R': {
		knots[0].first++;
		break;
	}
	case 'L': {
		knots[0].first--;
		break;
	}
	case 'U': {
		knots[0].second++;
		break;
	}
	case 'D': {
		knots[0].second--;
		break;
	}
	}

	for (int i = 0; i < knots.size() - 1; i++) {
		short dx = knots[i].first - knots[i + 1].first;
		short dy = knots[i].second - knots[i + 1].second;

		if (abs(dx) > 1 || abs(dy) > 1) {
			if(dx) knots[i + 1].first += dx > 0 ? 1 : -1;
			if(dy) knots[i + 1].second += dy > 0 ? 1 : -1;
		}
	}
}

void day9() {
	ifstream inp("day9.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	set<pair<int, int>> visited; // tail visited these coords
	vector<pair<int, int>> knots;
	//short knotsnumber = 10; // for part 1
	short knotsnumber = 10; // for part 2
	for (int i = 0; i < knotsnumber; i++) knots.push_back({ 1, 1 });

	string command;
	while (getline(inp, command)) {
		if (command.empty()) continue;
		for (int i = 0; i < stoi(command.substr(2, command.size() - 2)); i++) {
			calc_tpos(knots, command[0]);
			visited.insert(knots[knots.size()-1]);
		}
	}
	inp.close();

	//for (pair<int,int> x : visited) cout << "(" << x.first << ", " << x.second << ")\n";

	cout << "Visited coordinates number: " << visited.size() << "\n";
}