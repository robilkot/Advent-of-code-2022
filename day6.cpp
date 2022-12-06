#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <ctime>
//#define performance_comparison

using namespace std;

void day6_1() {
	ifstream inp("day6.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}
	string input;
	inp >> input;
	inp.close();

	int it = 0, answer = 0;
	while (it < input.size() - 1-3) {
		bool eq_2 = input[it] == input[it + 1], eq_3 = input[it] == input[it + 2], eq_4 = input[it] == input[it + 3];
		unsigned short sum = eq_2 + eq_3 + eq_4;
		if (sum==0 && input[it+1] != input[it+2] && input[it + 2] != input[it + 3] && input[it + 1] != input[it + 3]) {
			answer = it + 3 + 1;
			break;
		}
		it += sum >= 2 ? sum : 1;
	}

	cout << "The unique sequnce is after the character " << answer << "\n";
}

void day6_2() {
	ifstream inp("day6.txt");
	if (!inp.is_open()) {
		cout << "file not opened!\n";
		return;
	}
	string input;
	inp >> input;
	inp.close();
#ifdef performance_comparison
	clock_t start = clock();
#endif

	int it = 0, answer = 0;
	while (it < input.size() - 1 - 13) {
		int eq_first = 0;
		bool unique = 1, morethan1eq = 0;

		for (int i = 1; i <= 13; i++) {
			if (!unique) break;
			if (input[it] == input[it + i]) {
				unique = 0;
				if (eq_first) {
					morethan1eq = 1;
					break;
				}
				else eq_first = i;
			}
			for (int k = 1; k <= 13; k++) {
				if (!unique) break;
				if (k != i && input[it + i] == input[it + k]) unique = 0;
			}
		}

		if (unique) {
			answer = it + 13 + 1;
			break;
		}

		it += morethan1eq ? eq_first : 1;
	}
#ifdef performance_comparison
	clock_t end = clock();
#endif

	cout << "The message is after the character " << answer << "\n";

#ifdef performance_comparison
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("The time: %f seconds\n", seconds);

	start = clock();

	it = 0;
	answer = 0;
	while (it < input.size() - 1 - 13) {
		int eq_first = 0;
		bool unique = 1;

		for (int i = 0; i <= 13; i++) {
			if (!unique) break;
			for (int k = 1; k <= 13; k++) {
				if (!unique) break;
				if (k != i && input[it + i] == input[it + k]) unique = 0;
			}
		}

		if (unique) {
			answer = it + 13 + 1;
			break;
		}
		it++;
	}

	end = clock();

	cout << "The message is after the character " << answer << "\n";
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("The time: %f seconds\n", seconds);
#endif
}