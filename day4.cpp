#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void day4_1() {
	ifstream inp("day4.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	string currentstring;
	int answer = 0;
	while (getline(inp, currentstring)) {
		int sec1_max=0, sec2_max=0, sec1_min=0, sec2_min=0;
		size_t dashnumber = currentstring.find('-'), commanumber = currentstring.find(',');

		sec1_min = stoi(currentstring.substr(0, dashnumber));
		sec1_max = stoi(currentstring.substr(dashnumber + 1,commanumber - 1));

		dashnumber = currentstring.find('-',commanumber);

		sec2_min = stoi(currentstring.substr(commanumber + 1, dashnumber - 1));
		sec2_max = stoi(currentstring.substr(dashnumber + 1, currentstring.size()));

		if ((sec2_min>=sec1_min && sec2_max <= sec1_max) || (sec1_min>=sec2_min && sec1_max<=sec2_max)) answer++;
	}

	inp.close();
	cout <<  answer << " is a number of fully overlapping pairs\n";
}

void day4_2() {
	ifstream inp("day4.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	string currentstring;
	int answer = 0;
	while (getline(inp, currentstring)) {
		int sec1_max = 0, sec2_max = 0, sec1_min = 0, sec2_min = 0;
		size_t dashnumber = currentstring.find('-'), commanumber = currentstring.find(',');

		sec1_min = stoi(currentstring.substr(0, dashnumber));
		sec1_max = stoi(currentstring.substr(dashnumber + 1, commanumber - 1));

		dashnumber = currentstring.find('-', commanumber);

		sec2_min = stoi(currentstring.substr(commanumber + 1, dashnumber - 1));
		sec2_max = stoi(currentstring.substr(dashnumber + 1, currentstring.size()));

		if (sec2_min <= sec1_max && sec2_max >= sec1_min) answer++;
	}

	inp.close();
	cout << answer << " is a number of all overlapping pairs\n";
}