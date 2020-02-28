#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const unsigned int n = 303;
int arr[n][n];


void wave(int i, int j, int step) {
	if (arr[i][j] == 0) {
		int nextStep = step + 1;
		arr[i][j] = step;
		if (arr[i - 2][j + 1] == 0) {
			arr[i - 2][j + 1] = nextStep;
		}
		if (arr[i - 2][j - 1] == 0) {
			arr[i - 2][j - 1] = nextStep;
		}
		if (arr[i - 1][j + 2] == 0) {
			arr[i - 1][j + 2] = nextStep;
		}
		if (arr[i - 1][j - 2] == 0) {
			arr[i - 1][j - 2] = nextStep;
		}
		if (arr[i + 1][j + 2] == 0) {
			arr[i + 1][j + 2] = nextStep;
		}
		if (arr[i + 1][j - 2] == 0) {
			arr[i + 1][j - 2] = nextStep;
		}
		if (arr[i + 2][j + 1] == 0) {
			arr[i + 2][j + 1] = nextStep;
		}
		if (arr[i + 2][j - 1] == 0) {
			arr[i + 2][j - 1] = nextStep;
		}
	}
}

int main()
{
	// под конец сделат вывод в файл

	ifstream in("input1.txt");

	int N = 0;
	int i, j;
	char val = ' ';

	in >> N;

	cout << N;
	cout << endl;
	/*
	for (i = 0; i < N + 1; i++) {
		arr[i][0] = 1;
		arr[i][1] = 1;
		arr[i][N + 1] = 1;
		arr[i][N + 2] = 1;

		arr[0][i] = 1;
		arr[1][i] = 1;
		arr[N + 1][i] = 1;
		arr[N + 2][i] = 1;
	}
	*/

	for (i = 2; i < N + 1; i++) {
		for (j = 2; j < N + 1; j++) {
			in >> val;
			if (val == '@') {
				arr[i][j] = 2;
			}
			if (val == '.') {
				arr[i][j] = 0;
			}

			cout << arr[i, j];
		}
		cout << endl;
	}

	
	/*
	for (i = 0; i < N + 3; i++) {
		for (j = 0; j < N + 3; j++) {
			cout << arr[i, j];
		}

		cout << endl;
	}
	*/
	/*
	cout << endl;

	int grad = 0;

	for (i = 1; i < N + 1; i++) {
		for (j = 1; j < M + 1; j++) {
			if (arr[i][j] == 1) {
				grad++;
			}
			volna(i, j);
		}
	}

	cout << grad << endl;*/

	in.close();

	return 0;
}
