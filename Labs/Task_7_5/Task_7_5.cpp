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