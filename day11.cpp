#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#define PART1

using namespace std;

struct monkey {
	vector<long long> things;
	char operation;
	int secondoperand, test, dest_true, dest_false;
	long long score;
};

void nextround(vector<monkey>& monkeys, int& product) {
	for (int i = 0; i < monkeys.size(); i++) {
		monkeys[i].score += monkeys[i].things.size();
		while(!monkeys[i].things.empty()) {
			switch (monkeys[i].operation) {
			case '*': {
				if (monkeys[i].secondoperand == -1) monkeys[i].things[0] *= monkeys[i].things[0];
				else monkeys[i].things[0] *= monkeys[i].secondoperand;
				break;
			}
			case '+': {
				if (monkeys[i].secondoperand == -1) monkeys[i].things[0] *= 2;
				else monkeys[i].things[0] += monkeys[i].secondoperand;
				break;
			}
			}
#ifdef PART1
			monkeys[i].things[0] /= 3;
#endif // PART1
			monkeys[i].things[0] %= product;

			if (monkeys[i].things[0] % monkeys[i].test == 0) monkeys[monkeys[i].dest_true].things.push_back(monkeys[i].things[0]);
			else monkeys[monkeys[i].dest_false].things.push_back(monkeys[i].things[0]);

			monkeys[i].things.erase(monkeys[i].things.begin());
		}
	}
}

void day11() {
	ifstream inp("day11.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	int currentmonkey = -1, rounds, product = 1;
	vector<monkey> monkeys;

#ifdef PART1
	rounds = 20;
#else 
	rounds = 10000;
#endif

	string command;
	while (getline(inp, command)) {
		if (command.empty()) continue;
		switch (command[2]) {
		case 'n': {
			currentmonkey++;
			monkeys.push_back({});
			break;
		}
		case 'S': {
			for (int i = 18; i < command.size(); i += 4)
				monkeys[currentmonkey].things.push_back(stoi(command.substr(i, 2)));
			break;
		}
		case 'O': {
			monkeys[currentmonkey].operation = command[23];
			if (command[25] == 'o') monkeys[currentmonkey].secondoperand = -1;
			else monkeys[currentmonkey].secondoperand = stoi(command.substr(25));
			break;
		}
		case 'T': {
			monkeys[currentmonkey].test = stoi(command.substr(21, command.size() - 21));
			product *= monkeys[currentmonkey].test;
			break;
		}
		case ' ': {
			if (command[7] == 't') monkeys[currentmonkey].dest_true = stoi(command.substr(29));
			else if (command[7] == 'f') monkeys[currentmonkey].dest_false = stoi(command.substr(30));
			break;
		}
		}
	}
	inp.close();

	for(int i =0; i<rounds;i++) nextround(monkeys, product);

	long long firstmonkeyscore = 0, secondmonkeyscore = 0;
	for (int i = 0; i < monkeys.size(); i++) if (monkeys[i].score > firstmonkeyscore) firstmonkeyscore = monkeys[i].score;
	for (int i = 0; i < monkeys.size(); i++) if (monkeys[i].score > secondmonkeyscore && monkeys[i].score < firstmonkeyscore) secondmonkeyscore = monkeys[i].score;

	cout << "The monkey business is " << firstmonkeyscore * secondmonkeyscore << "\n";
}