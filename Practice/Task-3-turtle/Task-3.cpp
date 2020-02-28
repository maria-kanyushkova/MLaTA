#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Point {
	int type;
	int value;
};

const int N = 200;

Point arr[N][N];

int main()
{
	ifstream in("input6.txt");
	int n, m, i, j, sum;

	in >> n >> m;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			in >> arr[i][j].type;
			arr[i][j].value = 0;
		}
	}

	for (i = n - 2; i >= 0; i--) {
		sum = arr[i + 1][m - 1].value + arr[i][m - 1].type;
		arr[i][m - 1].value = sum;
	}

	for (j = m - 2; j >= 0; j--) {
		sum = arr[n - 1][j + 1].value + arr[n - 1][j].type;
		arr[n - 1][j].value = sum;
	}

	for (i = n - 2; i >= 0; i--) {
		for (j = m - 2; j >= 0; j--) {
			arr[i][j].value = arr[i][j].type + min(arr[i + 1][j].value, arr[i][j + 1].value);
		}
	}

	i = 0;
	j = 0;
	cout << arr[0][0].value + arr[n - 1][m - 1].type << endl;
	cout << "1 1" << endl;
	while (i < (n - 1) && j < (m - 1))
	{
		arr[i + 1][j].value > arr[i][j + 1].value ? j++ : i++;

		cout << i + 1 << " " << j + 1 << endl;
	}
	cout << n << " " << m << endl;
}
