#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

void day3_1() {
	ifstream inp("day3.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}
	
	string duplicates,currentstring;
	while (getline(inp, currentstring)) {
		string rucksackduplicates;
		for (int i=0; i < currentstring.size() / 2; i++) {
			for (int k= currentstring.size() / 2; k < currentstring.size(); k++) {
				if (currentstring[i] == currentstring[k] && rucksackduplicates.find(currentstring[i])==string::npos) rucksackduplicates.push_back(currentstring[i]);
			}
		}
		duplicates += rucksackduplicates;
	}

	int scorecounter = 0;
	for (char i : duplicates) scorecounter += i > 90 ? (i - 96) : (i - 38);

	inp.close();
	cout << scorecounter << " is a sum of priorities\n";
}

void day3_2() {
	ifstream inp("day3.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	string badges, currentstring, first, second, third;
	unsigned short currentelf = 0;
	while (getline(inp, currentstring)) {
		switch (currentelf) {
		case 0: {
			first = currentstring;
			currentelf++;
			break;
		}
		case 1: {
			second = currentstring;
			currentelf++;
			break;
		}
		case 2: {
			third = currentstring;
			bool foundbadge = 0;
			for (char m : first) {
				for (char n : second) {
					for (char k : third) {
						if (m == n && n == k) {
							badges.push_back(m);
							foundbadge = 1;
							break;
						}
					}
					if (foundbadge) break;
				}
				if (foundbadge) break;
			}
			first.clear();
			second.clear();
			third.clear();
			currentelf = 0;
		}
		}
	}

	int scorecounter = 0;
	for (char i : badges) scorecounter += i > 90 ? (i - 96) : (i - 38);

	inp.close();
	cout << scorecounter << " is a sum of priorities\n";
}