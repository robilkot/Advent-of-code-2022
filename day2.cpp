#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

void day2_1() {
	ifstream inp("day2.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	int scorecounter=0;
	string temp;
	while (getline(inp, temp)) {
		switch (temp[2]) {
		case 'X': {
			scorecounter += 1;
			switch (temp[0]) {
			case 'A': {
				scorecounter += 3;
				break;
			}
			case 'C': {
				scorecounter += 6;
				break;
			}
			}
			break;
		}
		case 'Y': {
			scorecounter += 2;
			switch (temp[0]) {
			case 'A': {
				scorecounter += 6;
				break;
			}
			case 'B': {
				scorecounter += 3;
				break;
			}
			}
			break;
		}
		case 'Z': {
			scorecounter += 3;
			switch (temp[0]) {
			case 'B': {
				scorecounter += 6;
				break;
			}
			case 'C': {
				scorecounter += 3;
				break;
			}
			}
			break;
		}
		}
		temp.clear();
	}
	inp.close();
	cout << "So your score is " << scorecounter <<". Not bad!\n";
}

void day2_2() {
	ifstream inp("day2.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	int scorecounter = 0;
	string temp;
	while (getline(inp, temp)) {
		switch (temp[2]) {
		case 'X': {
			//scorecounter += 0;
			switch (temp[0]) {
			case 'A': {
				scorecounter += 3;
				break;
			}
			case 'B': {
				scorecounter += 1;
				break;
			}
			case 'C': {
				scorecounter += 2;
				break;
			}
			}
			break;
		}
		case 'Y': {
			scorecounter += 3;
			switch (temp[0]) {
			case 'A': {
				scorecounter += 1;
				break;
			}
			case 'B': {
				scorecounter += 2;
				break;
			}
			case 'C': {
				scorecounter += 3;
				break;
			}
			}
			break;
		}
		case 'Z': {
			scorecounter += 6;
			switch (temp[0]) {
			case 'A': {
				scorecounter += 2;
				break;
			}
			case 'B': {
				scorecounter += 3;
				break;
			}
			case 'C': {
				scorecounter += 1;
				break;
			}
			}
			break;
		}
		}
		temp.clear();
	}
	inp.close();
	cout << "So your score is " << scorecounter << ". Not bad!\n";
}