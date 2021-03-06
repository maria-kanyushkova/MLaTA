﻿/*
3.9. Робот 2 (7).
Робот находится в точке плоскости с целыми координатами (X, Y) (0 ≤ X, Y ≤ 20, X + Y > 0). Он должен достичь цели, находящейся в начале координат. Ход заключается в продвижении на единицу по горизонтали (налево, направо) или вертикали (вверх, вниз). Если робот достигает цели, то немедленно останавливается. Найти количество способов достижения цели ровно за Z шагов (1 ≤ Z ≤ 20).
Ввод из файла INPUT.TXT. 
В единственной строке находятся через пробел X, Y и Z.
Вывод из файла OUTPUT.TXT. 
В единственной строке вывести количество способов достижения цели.
Примеры
Ввод 1   Ввод 2
1 0 1    0 1 3
Вывод 1  Вывод 2
1        5

Пояснение. Во втором примере возможны следующие варианты движения робота:
· (0,1) – (0,2) – (0,1) – (0,0);
· (0,1) – (1,1) – (0,1) – (0,0);
· (0,1) – (1,1) – (1,0) – (0,0);
· (0,1) – (-1,1) – (0,1) – (0,0);
· (0,1) – (-1,1) – (-1,0) – (0,0

канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int x, y, z;
	fin >> x >> y >> z;

	const int d = z + 1;
	const int x0 = d, y0 = d;
	x += x0;
	y += y0;
	const int w = x + d;
	const int h = y + d;

	// a[xi][yi][zi] - количество путей длины zi от клетки (x, y) до клетки (xi, yi)
	vector<vector<vector<long long>>> a(w, vector<vector<long long>>(h, vector<long long>(z + 1, 0)));
	a[x][y][0] = 1;
	for (int zi = 1; zi <= z; zi++) {
		for (int xi = 1; xi < w - 1; xi++) {
			for (int yi = 1; yi < h - 1; yi++) {
				if (xi == x0 && yi == y0) {
					continue;
				}
				a[xi][yi][zi] += a[xi - 1][yi][zi - 1];
				a[xi][yi][zi] += a[xi + 1][yi][zi - 1];
				a[xi][yi][zi] += a[xi][yi - 1][zi - 1];
				a[xi][yi][zi] += a[xi][yi + 1][zi - 1];
			}
		}
	}
	a[x0][y0][z] += a[x0 - 1][y0][z - 1];
	a[x0][y0][z] += a[x0 + 1][y0][z - 1];
	a[x0][y0][z] += a[x0][y0 - 1][z - 1];
	a[x0][y0][z] += a[x0][y0 + 1][z - 1];

	fout << a[x0][y0][z];

	return 0;
}