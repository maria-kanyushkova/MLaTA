/*
20.13. Арифметическая прогрессия (4)
Заданo N натуральных (целых положительных) чисел из диапазона [1; 10000]. Необходимо определить, можно ли из этих чисел в каком-либо порядке их следования составить арифметическую прогрессию.
Ввод. 
Первая строка файла INPUT.TXT содержит число тестовых блоков L (L ≤ 10). Каждый тестовый блок состоит из двух строк. В первой указывается количество чисел N (N ≤ 105), во второй - N чисел через пробел.
Вывод. 
Результат в файле OUTPUT.TXT. Для каждого тестового блока выводится единственная строка со значением Yes или No – можно или нет составить арифметическую прогрессию.
Пример
Ввод
2
3
5 9 1
4
11 13 15 13
Вывод
Yes
No

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int l;
	fin >> l;
	for (int i = 0; i < l; i++) {
		int n;
		fin >> n;
		vector<int> x(n);
		for (int j = 0; j < n; j++) {
			fin >> x[j];
		}
		sort(x.begin(), x.end());

		if (n == 1) {
			fout << "Yes\n";
			continue;
		}

		bool ok = true;
		int d = x[1] - x[0];
		for (int j = 2; j < n; j++) {
			if (x[j] - x[j - 1] != d) {
				ok = false;
				break;
			}
		}

		fout << (ok ? "Yes\n" : "No\n");

	}
}