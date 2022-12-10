#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void display(const vector<vector<char>>& m) {
	for (int i = 0; i < m.size(); i++) {
		for (char c : m[i]) cout << c;
		cout << "\n";
	}
}

void nextcycle(int& currentcycle, int& X, int& answer, vector<vector<char>>& crt) {
	short crtpos = (currentcycle - 1) % 40;
	if (crtpos == X || crtpos == X - 1 || crtpos == X + 1) crt[currentcycle / 40][crtpos] = '0';
	/*if (currentcycle % 5 == 0) {
		system("CLS");
		display(crt);
	}*/
	if ((currentcycle - 20) % 40 == 0 && currentcycle < 220 + 1) answer += currentcycle * X;
	currentcycle++;
}

void day10() {
	ifstream inp("day10.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	vector<vector<char>> crt;
	for (int i = 0; i < 6; i++) {
		crt.push_back({});
		for (int k = 0; k < 40; k++) crt[i].push_back(' ');
	}

	string command;
	int X=1, answer=0, currentcycle = 1;
	while(getline(inp, command)) {
		nextcycle(currentcycle, X, answer,crt);
		if (command.substr(0, 4) == "addx") {
			nextcycle(currentcycle, X, answer, crt);
			X += stoi(command.substr(5, command.size()-5));
		}
	}
	inp.close();
	display(crt);
	cout << "\nThe sum for part 1 is " << answer << "\n";
}