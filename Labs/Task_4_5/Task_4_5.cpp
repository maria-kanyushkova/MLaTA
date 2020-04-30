/*
4.5. Маршрут (6)
Дана матрица N ´ N, заполненная целыми положительными числами. Путь по матрице начинается в левом верхнем углу. За один ход можно пройти в соседнюю по вертикали или горизонтали клетку (если она существует). Нельзя ходить по диагонали, нельзя оставаться на месте. Требуется найти максимальную сумму чисел, стоящих в клетках по пути длиной K клеток (клетку можно посещать несколько раз).
Ограничения: 2 ≤ N ≤ 20, элементы матрицы имеют значения от 1 до 9999, 1 ≤ K ≤ 20.
Ввод из файла INPUT.TXT. 
В первой строке находятся разделенные пробелом числа N и K. Затем идут N строк по N чисел в каждой.
Вывод в файл OUTPUT.TXT. 
Вывести в первой строке максимальную сумму. В следующих K строках – соответствующий маршрут в виде координат клеток.
Пример
Ввод
5 7
1 1 1 1 1
1 1 3 1 9
1 1 6 1 1
1 1 3 1 1
1 1 1 1 1
Вывод
21
1 1
1 2
1 3
2 3
3 3
4 3
3 3

Подсказка. В цикле по количеству клеток пути определить для каждой клетки, какое максимальное значение может быть получено в соседних с ней клетках с учетом предыдущих шагов.

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 20000;

int max4(int a, int b, int c, int d) {
	return max(max(a, b), max(c, d));
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n, k;
	fin >> n >> k;

	vector<vector<int>> x(n + 2, vector<int>(n + 2, -INF));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> x[i + 1][j + 1];
		}
	}

	// a[i][j][ki] - максимально возможная сумма чисел для пути длины ki, заканчивающегося в клетке x[i][j]
	vector<vector<vector<long long>>> a(n + 2, vector<vector<long long>>(n + 2, vector<long long>(k, -INF)));
	a[1][1][0] = x[1][1];
	for (int ki = 1; ki < k; ki++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				a[i][j][ki] = x[i][j] + max4(
					a[i - 1][j][ki - 1],
					a[i + 1][j][ki - 1],
					a[i][j - 1][ki - 1],
					a[i][j + 1][ki - 1]
				);
			}
		}
	}

	// mi, mj - координаты последней клетки пути
	// m - максимальная сумма чисел для пути длины k
	int mi = 1, mj = 1;
	int m = -INF;
	k--;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j][k] > m) {
				mi = i;
				mj = j;
				m = a[i][j][k];
			}
		}
	}

	// строим путь от конечной клетки до начальной
	vector<pair<int, int>> path;
	path.push_back({ mi, mj });
	while (k > 0) {
		k--;
		int mn = max4(
			a[mi - 1][mj][k],
			a[mi + 1][mj][k],
			a[mi][mj - 1][k],
			a[mi][mj + 1][k]
		);
		if (mn == a[mi - 1][mj][k]) {
			mi--;
		}
		else if (mn == a[mi + 1][mj][k]) {
			mi++;
		}
		else if (mn == a[mi][mj - 1][k]) {
			mj--;
		}
		else if (mn == a[mi][mj + 1][k]) {
			mj++;
		}

		path.push_back({ mi, mj });
	}

	fout << m << endl;
	for (auto it = path.rbegin(); it != path.rend(); ++it) {
		fout << it->first << ' ' << it->second << endl;
	}

	return 0;
}