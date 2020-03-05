#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void min_squares(const int size)
{
	vector<int> path(size + 1);
	vector<int> dynamics(size + 1);
	int prev = 0;
	int left = 0;
	int right = 0;
	int minSquare = 0;

	for (int i = 0; i <= size; i++) {
		dynamics[i] = i;
		for (int j = 0; j <= i; j++) {
			const int square = j * j;
			if (square > i) {
				break;
			}
			prev = i - square;
			left = dynamics[i];
			right = 1 + dynamics[prev];
			minSquare = min(left, right);
			if (right < left) {
				path[i] = i - prev;
			}
			dynamics[i] = minSquare;
		}
	}

	const int result = dynamics[size];
	int current = path[size];

	int lastSquare = size;

	for (int i = 0; i < result - 1; i++) {
		if (path[size - current * i] != 0) {
			current = path[size - current * i];
			lastSquare -= current;
			cout << current << ' ';
		}
		else {
			cout << 1 << ' ';
		}
	}
	cout << lastSquare << ' ' << endl << result << endl;
}


int main()
{
	int input = 0;
	ifstream in("input4.txt");
	in >> input;
	min_squares(input);
}
