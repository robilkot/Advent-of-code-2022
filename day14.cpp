#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#define PART2

constexpr int XOFFSET = 0;
constexpr int WIDTH = 800;
constexpr int HEIGHT = 200;

using namespace std;

void displaymap(const vector<vector<char>>& m) {
    int answer = 0;
    for (int i = 0; i < m.size(); i++) {
        for (char c : m[i]) {
            cout << c;
            if (c == 'o') answer++;
        }
        cout << "\n";
    }
    cout << "\nThe answer is " << answer << "\n";
}

bool computesand(const pair<int, int>& sandsrc, queue<pair<int,int>>& q, vector<vector<char>>& map) {
    if (map[sandsrc.second][sandsrc.first] == 'o') return 0;
    q.push(sandsrc);
    map[sandsrc.second][sandsrc.first] = 'o';

    bool finished = 1, endreached = 0;
    for (int qsize = q.size(), i=0; i < qsize; i++) {
        const pair<int, int> oldpos = q.front();
        pair<int,int> newpos = oldpos;
       
        if (oldpos.second == HEIGHT - 1) endreached = 1;
        if (endreached) {
            for (int i = 0; !q.empty(); i++) {
                map[q.front().second][q.front().first] = '~';
                q.pop();
            }
            finished = 1;
            break;
        }

        q.pop();
        if (map[oldpos.second + 1][oldpos.first] != 'o' && map[oldpos.second + 1][oldpos.first] != '#') {
            map[oldpos.second + 1][oldpos.first] = 'o';
            newpos = { oldpos.first, oldpos.second + 1 };
            finished = 0;
        }
        else if (map[oldpos.second + 1][oldpos.first - 1] != 'o' && map[oldpos.second + 1][oldpos.first - 1] != '#') {
            map[oldpos.second + 1][oldpos.first - 1] = 'o';
            newpos = { oldpos.first - 1, oldpos.second + 1 };
            finished = 0;
        }
        else if (map[oldpos.second + 1][oldpos.first + 1] != 'o' && map[oldpos.second + 1][oldpos.first + 1] != '#') {
            map[oldpos.second + 1][oldpos.first + 1] = 'o';
            newpos = { oldpos.first + 1, oldpos.second + 1 };
            finished = 0;
        }
        if (!finished) {
            map[oldpos.second][oldpos.first] = ' ';
            q.push(newpos);
        }  
    }
    return !finished;
}

void day14() {
    ifstream inp("day14.txt");
    if (!inp.is_open()) {
        cout << "file not opened!\n";
        return;
    }

    int minheight = 0;
    vector<vector<char>> map;
    for (int i = 0; i < HEIGHT; i++) {
        map.push_back({});
        for (int k = 0; k < WIDTH; k++) map[i].push_back(' ');
    }

    for (string currentline; getline(inp, currentline); ) {
        while (!currentline.empty()) {
            pair<int, int> coords1, coords2;
            size_t arrowpos = currentline.find(">"), commapos = currentline.find(",");
            if (arrowpos == string::npos || commapos == string::npos) break;

            coords1.first = stoi(currentline.substr(0, commapos)) - XOFFSET;
            coords1.second = stoi(currentline.substr(commapos+1, arrowpos - 2));
            currentline.erase(0, arrowpos + 1);

            commapos = currentline.find(",");
            coords2.first = stoi(currentline.substr(0, commapos)) - XOFFSET;
            coords2.second = stoi(currentline.substr(commapos + 1));
#ifdef PART2
            if (coords2.second > minheight) minheight = coords2.second;
            else if (coords1.second > minheight) minheight = coords1.second;
#endif
            if (coords1.second == coords2.second) {
                int maximum = max(coords1.first, coords2.first), minimum = min(coords1.first, coords2.first);
                for (int i = minimum; i < maximum + 1; i++) map[coords1.second][i] = '#';
            }
            else if (coords1.first == coords2.first) {
                int maximum = max(coords1.second, coords2.second), minimum = min(coords1.second, coords2.second);
                for (int i = minimum; i < maximum + 1; i++) map[i][coords1.first] = '#';
            }
        }
    }
#ifdef PART2
    for (int i = 0; i < WIDTH; i++) map[minheight + 2][i] = '#';
#endif

    queue<pair<int, int>> q;
    while (computesand({ 500 - XOFFSET,0 }, q, map));
    displaymap(map);
}