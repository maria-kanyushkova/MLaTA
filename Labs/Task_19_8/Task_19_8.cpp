/*
19.8. Сапер (3)
В некоторых клетках прямоугольной таблицы M×N (0 < M, N ≤ 10) имеются “мины” (игра Minesweeper). Проставить во всех клетках таблицы либо символ мины ‘*’, либо число от 0 до 8, показывающее число мин в соседних клетках по горизонтали, вертикали или диагонали.
Ввод. Первая строка файла INPUT.TXT содержит целые числа M и N через пробел, задающие число строк и столбцов соответственно. Каждая из последующих M строк содержит ровно N символов. Безопасные клетки обозначаются ‘+’, а мины ‘*’.
Вывод. В файл OUTPUT.TXT вывести M строк по N символов.
Пример
Ввод
3 5
++*+*
**+++
+*+**
Вывод
23*2*
**443
3*3**

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <fstream>

using namespace std;

const int Mmax = 12;
const int Nmax = 12;

char arr[Mmax][Nmax];

int count(int i, int j) {
    int count = 0;
    if (arr[i - 1][j - 1] == '*') {
        count++;
    }
    if (arr[i][j - 1] == '*') {
        count++;
    }
    if (arr[i + 1][j - 1] == '*') {
        count++;
    }
    if (arr[i + 1][j] == '*') {
        count++;
    }
    if (arr[i + 1][j + 1] == '*') {
        count++;
    }
    if (arr[i][j + 1] == '*') {
        count++;
    }
    if (arr[i - 1][j + 1] == '*') {
        count++;
    }
    if (arr[i - 1][j] == '*') {
        count++;
    }
    return count;
}


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int m, n;
    fin >> m >> n;
    for (int i = 0; i < m + 2; i++) {
        arr[i][0] = '.';
        arr[i][n + 1] = '.';
    }

    for (int j = 0; j < n + 2; j++) {
        arr[0][j] = '.';
        arr[m + 1][j] = '.';
    }

    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            fin >> arr[i][j];
        }
    }

    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (arr[i][j] == '+') {
				arr[i][j] = count(i, j) + '0';
            }
        }
    }

	for (int i = 1; i < m + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			fout << arr[i][j];
		}
		fout << "\n";
	}
}