#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void day5_1() {
	ifstream inp("day5.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	string currentstring;
	vector<string> crates;
	bool gotcrates = 0;

	while (getline(inp, currentstring)) {
		if (currentstring.empty()) {
			gotcrates = 1;
			continue;
		}
		if (!gotcrates) {	
			int k = 0;
			for (int i = 1; i < currentstring.length(); i += 4, k++) {
				if (i == 1) k = 0;
				if (k+1 > crates.size()) crates.push_back({});
				if(currentstring[i]!=' ') crates[k].push_back(currentstring[i]);
			}
			continue;
		}

		size_t frompos = currentstring.find("from"), topos = currentstring.find("to");
		int numbertomove = stoi(currentstring.substr(5, frompos-6));
		int stack_from = stoi(currentstring.substr(frompos+5,topos-4))-1, stack_dest = stoi(currentstring.substr(topos + 3, currentstring.size()-1))-1;

		for (int i = 0; i < numbertomove; i++) {
			crates[stack_dest].insert(crates[stack_dest].begin(), crates[stack_from][0]);
			crates[stack_from].erase(0, 1);
		}
	}
	for (int i = 0; i < crates.size(); i++) {
		cout << crates[i][0];
	}
	cout << "\n";

	inp.close();
}

void day5_2() {
	ifstream inp("day5.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	string currentstring;
	vector<string> crates;
	bool gotcrates = 0;

	while (getline(inp, currentstring)) {
		if (currentstring.empty()) {
			gotcrates = 1;
			continue;
		}
		if (!gotcrates) {
			int k = 0;
			for (int i = 1; i < currentstring.length(); i += 4, k++) {
				if (i == 1) k = 0;
				if (k + 1 > crates.size()) crates.push_back({});
				if (currentstring[i] != ' ') crates[k].push_back(currentstring[i]);
			}
			continue;
		}

		size_t frompos = currentstring.find("from"), topos = currentstring.find("to");
		int numbertomove = stoi(currentstring.substr(5, frompos - 6));
		int stack_from = stoi(currentstring.substr(frompos + 5, topos - 4)) - 1, stack_dest = stoi(currentstring.substr(topos + 3, currentstring.size() - 1)) - 1;

		for (int i = 0; i < numbertomove; i++) {
			crates[stack_dest].insert(crates[stack_dest].begin(), crates[stack_from][numbertomove-1-i]);
			crates[stack_from].erase(numbertomove-1-i, 1);
		}
	}
	for (int i = 0; i < crates.size(); i++) {
		cout << crates[i][0];
	}
	cout << "\n";

	inp.close();
}