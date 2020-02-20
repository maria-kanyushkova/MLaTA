#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


const unsigned int n = 201;
const unsigned int m = 201;
int arr[n][m];


void volna(int i, int j) {
	if (arr[i][j] == 1) {
		arr[i][j] = 0;
		volna(i + 1, j);
		volna(i - 1, j);
		volna(i, j + 1);
		volna(i, j - 1);
	}
}

int main()
{
	ifstream in("input3.txt"); 

	int N = 0;
	int M = 0;

	int i = 0;
	int j = 0;

	char val = ' ';

	in >> N >> M;

	for (i = 0; i < N + 2; i++) {
		arr[i][0] = 0;
		arr[i][M + 2] = 0;
	}

	for (j = 0; i < M + 2; i++) {
		arr[0][j] = 0;
		arr[0][N + 2] = 0;
	}

	for (i = 1; i < N + 1; i++) {
		for (j = 1; j < M + 1; j++) {
			in >> val;
			if (val == '#') {
				arr[i][j] = 1;
			}
			if (val == '.') {
				arr[i][j] = 0;
			}
		}
	}

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

	cout << grad << endl;
		
	in.close();   

	return 0;
}
