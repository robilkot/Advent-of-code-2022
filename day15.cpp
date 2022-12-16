#include <iostream>
#include <fstream>
#include <string>
#include <vector>

constexpr int CHECKLINE = 2000000;

using namespace std;

int manhdistance(const pair<pair<int, int>, pair<int, int>>& p) {
	return abs(p.first.first - p.second.first) + abs(p.first.second - p.second.second);
}

void day15() {
	ifstream inp("day15.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	vector<pair<pair<int, int>, pair<int, int>>> objects;
	int linenumber = 0;
	int leftborder = 0, rightborder = 0;
	for (string currentline; getline(inp, currentline); linenumber++) {
		if (currentline.empty()) continue;
		objects.push_back({});
		
		int leftbordertest = 0, rightbordertest = 0;

		size_t commapos = currentline.find(","), secondxpos = currentline.find("x=", commapos)+2;
		objects[linenumber].first.first = stoi(currentline.substr(12, commapos - 13 + 1));
		objects[linenumber].first.second = stoi(currentline.substr(commapos + 4, currentline.find(":") - 1 - commapos));
		
		commapos = currentline.find(",", secondxpos);
		objects[linenumber].second.first = stoi(currentline.substr(secondxpos, commapos - secondxpos));
		objects[linenumber].second.second = stoi(currentline.substr(commapos + 4, currentline.size() - 1 - commapos));

		if (!linenumber) leftborder = objects[linenumber].first.first;
		leftbordertest = objects[linenumber].first.first - manhdistance(objects[linenumber]);
		if (leftbordertest < leftborder) {
			leftborder = leftbordertest;
			continue;
		}
		rightbordertest = objects[linenumber].first.first + manhdistance(objects[linenumber]);
		if (rightbordertest > rightborder) rightborder = rightbordertest;
	}

	int answer = 0;
	for (int i = leftborder; i < rightborder; i++) {
		bool visible = 0;
		for (int k = 0; k < objects.size(); k++) {
			if (i == objects[k].second.first && CHECKLINE == objects[k].second.second) continue;
			int dist1 = manhdistance(objects[k]), dist2 = manhdistance({ { i, CHECKLINE }, { objects[k].first.first, objects[k].first.second } });	
			if (dist1 >= dist2) {
				visible = 1;
				break;
			}
		}
		if (visible) answer++;
	}
	cout << "That was tough, but the answer is " << answer << "\n";
}
