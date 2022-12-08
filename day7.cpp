#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void PrintMap(const map<string, int>& m)
{
	for (const auto& n : m) cout << n.first << " <-> " << n.second << "\n";
}

string ReadNthLine(const string& filename, int N)
{
	ifstream in(filename.c_str());
	string s;
	for (int i = 0; i < N; ++i) getline(in, s);
	return getline(in, s) ? s : "";
}

void CountFolderSize(map<string, int>& m, map<string, int>::iterator it) {
	for (auto it2 = m.begin(); it2 != m.end(); ++it2) {
		if (it == it2) continue;
		string parentfor2 = it2->first.substr(0, it2->first.rfind('/'));
		if (parentfor2.empty()) parentfor2 = "/";
		if (parentfor2.size() >= it->first.size()) {
			if (m.find(parentfor2) == it || m.find(parentfor2) == m.end()) {
				CountFolderSize(m, it2);
				it->second += it2->second;		
			}
		}
	}
}

void day7() {
	ifstream inp("day7.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}

	string currentpath, currentstring;
	map<string, int> folders;

	for (int linenumber = 1; getline(inp, currentstring); linenumber++) {
		string firstword = currentstring.substr(0, currentstring.find(' '));
		if (firstword == "$") { // commands
			switch (currentstring[2]) {
			case 'l': { // ls command
				int currentfolderfilessize = 0;
				for (int i = 0; ; i++) {
					string currentfile = ReadNthLine("day7.txt", linenumber + i);
					if (currentfile[0] == '$' || currentfile.empty()) break; // if new command appears or the file ends
					if (currentfile[0] == 'd') continue; // if dir appears
					currentfolderfilessize += stoi(currentfile.substr(0, currentfile.rfind(' ')));
				}
				folders[currentpath] = currentfolderfilessize;
				break;
				}
			case 'c': { // cd command
				string newfolder = currentstring.substr(5, currentstring.size() - 5);
				if (newfolder == "..") {
					size_t bslashpos = currentpath.rfind('/');
					if (bslashpos) currentpath = currentpath.substr(0, bslashpos);
					else currentpath = "/";
					break;
				}
				if(newfolder != "/" && currentpath[currentpath.size()-1]!='/') currentpath += '/';
				currentpath += newfolder;
			} 
			}
		}
	}
	inp.close();

	CountFolderSize(folders, folders.begin());

	auto it_answer = folders.begin();
	for (auto it=folders.begin(); it != folders.end(); ++it) {
		if (folders.begin()->second - it->second < 40000000) {
			if (it->second < it_answer->second) it_answer = it;
		}
	}
	cout << "We should delete the folder " << it_answer->first << " with size of " << it_answer->second << "\n";

	for (auto it = folders.begin(); it != folders.end(); ) {
		if (it->second > 100000) it = folders.erase(it);
		else ++it;
	}

	int answer = 0;
	for (auto it = folders.begin(); it != folders.end(); it++) answer += it->second;

	cout << "The sum of folders <=100000 is " << answer << "\n";
}