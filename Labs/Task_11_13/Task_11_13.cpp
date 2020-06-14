/*
11.13. Длина линии (6)
Имеется круг радиуса R с центром в начале координат. Заданы две точки (X1, Y1) и (X2, Y2). Требуется найти минимальную длину линии, соединяющей эти точки, но не пересекающей внутренность круга.
Ввод из файла INPUT.TXT. В первой строке находится целое число N – количество блоков входных данных. Далее следуют N строк, каждая из которых содержит пять вещественных чисел через пробел – X1, Y1, X2, Y2 и R.
Вывод в файл OUTPUT.TXT. Для каждого блока входных данных выводится одно вещественное число с двумя знаками после запятой - минимальная длина линии.
Пример
Ввод
2
1 1 -1 -1 1
1 1 -1 1 1
Вывод
3.571
2.000

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

const double PI = atan(1) * 4;

// точка на плоскости
struct Point {
	double x, y;

	// расстояние до точки
	double dist(Point p) const {
		return hypot(p.x - x, p.y - y);
	}

	// угол к точке
	double angle(Point p) const {
		return atan2(p.y - y, p.x - x);
	}
};

// прямая
struct Line {
	double a, b, c;

	// прямая по 2 точкам
	Line(Point p1, Point p2) {
		if (p1.x == p2.x) {
			a = 0;
			b = 1;
			c = -p1.x;
			return;
		}

		double k = (p2.y - p1.y) / (p2.x - p1.x);
		a = 1;
		b = -k;
		c = k * p1.x - p1.y;
	}

	// расстояние от прямой до точки
	double dist(Point p) {
		return abs(a * p.x + b + p.y + c) / hypot(a, b);
	}
};

// нормализует угол таким образом, чтобы он был минимальным
double normalizeAngle(double a) {
	while (a < 0) {
		a += 2 * PI;
	}
	while (a > 2 * PI) {
		a -= 2 * PI;
	}

	if (a > PI) {
		return abs(a - 2 * PI);
	}
	return a;
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	fout << fixed << setprecision(6);

	// начало координат
	const Point p0{ 0, 0 };

	int n;
	fin >> n;
	for (int t = 0; t < n; t++) {
		double x1, x2, y1, y2, r;
		fin >> x1 >> y1 >> x2 >> y2 >> r;
		Point p1{ x1, y1 };
		Point p2{ x2, y2 };
		Line l(p1, p2);

		if (l.dist(p0) > r) {
			// прямая между точками не пересекается с окружностью
			fout << p1.dist(p2) << endl;
			continue;
		}

		// углы от начала координат до точек
		double a1 = p0.angle(p1);
		double a2 = p0.angle(p2);

		// углы между точками касания и прямыми до точек
		double b1 = acos(r / p1.dist(p0));
		double b2 = acos(r / p2.dist(p0));

		// длины касательных
		double d1 = p1.dist(p0) * sin(b1);
		double d2 = p2.dist(p0) * sin(b2);

		// возможные дуги между точками касания
		double c1 = normalizeAngle((a1 - b1) - (a2 + b2));
		double c2 = normalizeAngle((a1 + b1) - (a2 - b2));

		// длина кратчайшей дуги между касательными
		double arc = min(c1, c2) * r;

		double ans = d1 + d2 + arc;
		fout << ans << endl;
	}
}