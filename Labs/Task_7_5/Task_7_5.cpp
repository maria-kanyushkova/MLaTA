/*
7.5. Волки и овцы (8) 
На координатной плоскости заданы отрезками N волков и M овец. Пастух с ружьем находится в начале координат. Выстрел поражает всех животных по направлению полета пули. Найти наименьшее число выстрелов для того, чтобы убить всех волков и не тронуть овец.
Ввод из файла INPUT.TXT. В первой строке задаются через пробел значения N и M (1 ≤ N, M ≤ 103). В следующих N строках - целочисленные координаты начала (X1, Y1) и конца (X2, Y2) отрезка, соответствующего волку (-1000 ≤ X1, X2 ≤ 1000; 1 ≤Y1, Y2 ≤ 1000). Аналогично в следующих M строках указывается положение овец.
Вывод в файл OUTPUT.TXT единственного целого числа либо сообщения “No solution”.
Пример
Ввод
2 1
1 1 2 3
-5 4 2 2
999 1000 1000 999

Вывод
1

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

enum AnimalType {
	Wolf,
	Sheep,
};

enum PointType {
	Left,
	Right,
};

struct Point {
	double a; // угол относительно начала координат
	AnimalType at;
	PointType pt;
	int index; // индекс животного
};

struct Animal {
	Point l, r;
};

Animal readAnimal(istream& in, AnimalType at, int index) {
	int x1, x2, y1, y2;
	in >> x1 >> y1 >> x2 >> y2;
	double a1 = atan2(y1, x1);
	double a2 = atan2(y2, x2);
	if (a1 > a2) {
		swap(a1, a2);
	}

	return { {a1, at, Left, index}, {a2, at, Right, index} };
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n, m;
	fin >> n >> m;

	vector<Point> p;
	vector<Animal> wolfs;
	vector<Animal> sheeps;

	for (int i = 0; i < n; i++) {
		Animal a = readAnimal(fin, Wolf, i);
		wolfs.push_back(a);
		p.push_back(a.l);
		p.push_back(a.r);
	}
	for (int i = 0; i < m; i++) {
		Animal a = readAnimal(fin, Sheep, i);
		sheeps.push_back(a);
		p.push_back(a.l);
		p.push_back(a.r);
	}

	// сортируем точки по возрастанию угла
	sort(p.begin(), p.end(), [](Point a, Point b) {
		const double eps = 1e-6;
		if (abs(a.a - b.a) < eps) {
			return a.pt == Left && b.pt == Right;
		}
		return a.a < b.a;
	});

	vector<bool> alive(n, true); // флаги, указывающие на то, живы ли волки с определенными индексами
	int sheepCount = 0; // количество овец под прицелом
	set<int> wolfsToShoot; // индексы волков под прицелом
	double sheepL; // угол точки, с которой начинаются отрезки с овцами
	double sheepR; // угол точки, на которой заканчиваются отрезки с овцами
	int ans = 0; // количество выстрелов

	for (int i = 0; i < p.size(); i++) {
		if (p[i].pt == Left && p[i].at == Wolf) {
			// встретили левую границу волка, добавляем в список волков под прицелом
			wolfsToShoot.insert(p[i].index);
		}
		else if (p[i].pt == Right && p[i].at == Wolf && alive[p[i].index]) {
			// дошли до правой границы живого волка
			set<int> wolfsToSkip; // волки, в которых не можем выстрелить, если мешают овцы
			if (sheepCount > 0) {
				// если мешают овцы, то стреляем левее и ищем волков, в которых не можем попасть
				for (int j : wolfsToShoot) {
					if (wolfs[j].l.a > sheepL) {
						if (wolfs[j].r.a < sheepR) {
							// случай, когда в волка невозможно выстрелить, не попав в овцу
							fout << "No solution\n";
							return 0;
						}

						wolfsToSkip.insert(j);
					}
				}
				for (int j : wolfsToSkip) {
					wolfsToShoot.erase(j);
				}
			}

			// стреляем
			for (int j : wolfsToShoot) {
				alive[j] = false;
			}
			wolfsToShoot = wolfsToSkip;
			ans++;
		}
		else if (p[i].pt == Left && p[i].at == Sheep) {
			if (sheepCount == 0) {
				sheepL = p[i].a;
			}
			sheepR = max(sheepR, sheeps[p[i].index].r.a);
			sheepCount++;
		}
		else if (p[i].pt == Right && p[i].at == Sheep) {
			sheepCount--;
		}
	}

	fout << ans << endl;
}