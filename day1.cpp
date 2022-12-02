#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

void day1() {
	ifstream inp("day1.txt");
	if (!inp.is_open()) cout << "file not opened!\n";

	vector<int> elvesfood({ 0 });
	int iterator = 0, maxnumber = 0, secondnumber = 0, thirdnumber = 0;
	string temp;
	while (getline(inp, temp)) {
		if (temp.empty()) {
			if (elvesfood[maxnumber] < elvesfood[iterator]) {
				maxnumber = iterator;
			}
			iterator++;
			elvesfood.push_back(0);
			continue;
		}
		elvesfood[iterator] += stoi(temp);
		temp.clear();
	}

	for (int i = 0; i < elvesfood.size(); i++) {
		if (elvesfood[i] > elvesfood[secondnumber] && i != maxnumber) secondnumber = i;

	}
	for (int i = 0; i < elvesfood.size(); i++) {
		if (elvesfood[i] > elvesfood[thirdnumber] && i != secondnumber && i != maxnumber) thirdnumber = i;
	}

	cout << "Elf with 1st amount of food is " << maxnumber + 1 << ". It has " << elvesfood[maxnumber] << " points of food\n";
	cout << "Elf with 2nd amount of food is " << secondnumber + 1 << ". It has " << elvesfood[secondnumber] << " points of food\n";
	cout << "Elf with 3rd amount of food is " << thirdnumber + 1 << ". It has " << elvesfood[thirdnumber] << " points of food\n\n";
	cout << "The total food of top-3 elves is " << elvesfood[maxnumber] + elvesfood[secondnumber] + elvesfood[thirdnumber] << "\n";
}