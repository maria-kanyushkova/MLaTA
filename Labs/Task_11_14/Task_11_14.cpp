﻿/*
11.14.Распил бревен
Лесопильный комбинат выполняет заказ на распил брусьев для строительства детского городка.Все готовые брусья должны иметь форму треугольных призм, основаниями которых являются равнобедренные треугольники.Для изготовления брусьев закуплены заготовки в виде половинок продольно распиленных бревен.Заготовки не являются идеальными половинками цилиндров, поэтому при изготовлении бруса необходимо учитывать форму заготовок.Комбинат заинтересован в изготовлении бруса с наибольшей возможной площадью поперечного сечения.
Для каждой заготовки измеряется несколько сечений.Каждое из них задано в виде ломаной, представленной координатами ее вершин(x0, y0), (x1, y1), …, (xN, yN) в порядке их следования.Координаты вершин ломаной удовлетворяют следующим условиям :
· x0 < x1 < x2 < … < xN;
· xi = 0 для некоторого 0 < i < N;
· y0 = yN = 0
· для всех i от 1 до(N - 1) выполнено условие yi > 0.
С учетом описанных требований необходимо найти максимально возможную площадь равнобедренного треугольника, удовлетворяющего следующим условиям :
· основание треугольника лежит на оси абсцисс;
· основание симметрично относительно начала координат;
· треугольник полностью лежит внутри каждого из измеренных сечений заготовки.
Требуется написать программу, которая по заданным сечениям заготовки вычислит максимально возможную площадь искомого равнобедренного треугольника.
Ввод.
Первая строка входного файла содержит целое число K – количество измеренных сечений(1 ≤ K ≤ 1000).Далее следуют описания каждого из K сечений.В первой строке описания сечения содержится число NK – количество звеньев ломаной.За ней следуют(NK + 1) строк, каждая из которых содержит пару целых чисел xi и yi – координаты вершин ломаной сечения в порядке их следования.Сумма Ni не более 105, координаты вершин по модулю не превышают 109.
Вывод.
Выходной файл должен содержать одно вещественное число – наибольшую возможную площадь треугольника.Эта площадь должна иметь абсолютную или относительную погрешность не более 10 - 6, что означает следующее.Пусть выведенное число равно x, а в правильном ответе оно равно y.Ответ будет считаться правильным, если значение выражения | x - y| / max{ 1, | y | } не превышает 10 - 6.

Примеры

Ввод
2
5
- 6 0
- 3 5
- 2 4
0 6
2 3
5 0
5
- 6 0
- 2 3
- 1 6
0 6
1 6
7 0

Вывод
25.0

Visual Studio 2019
Канюшкова Мария ПС-21
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point {
	long x, y;
};

vector<Point> points; // все точки всех сечений
double maxHeight = 1e+10; // максимально возможная высота треугольники

// Макс. площадь по половине длины основания
double maxSquare(double l) {
	double minHeight = maxHeight;
	for (int i = 0; i < points.size(); i++) {
		auto& p = points[i];
		if (p.x >= l) {
			continue;
		}

		double h = p.y * l / (l - p.x); // выводится через подобные треугольники
		minHeight = min(minHeight, h);
	}

	return minHeight * l;
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	double lo = 0;
	double hi = 1e+10; // максимально возможная половина длины основания

	int k;
	fin >> k;
	for (int i = 0; i < k; i++) {
		int n;
		fin >> n;
		for (int j = 0; j <= n; j++) {
			Point p;
			fin >> p.x >> p.y;
			p.x = abs(p.x); // отбрасываем знак для удобства дальнейшей работы

			if (p.y == 0) {
				hi = min(hi, double(p.x));
			}
			if (p.x == 0) {
				maxHeight = min(maxHeight, double(p.y));
			}

			points.push_back(p);
		}
	}

	// тернарный поиск
	while (hi - lo > 1e-7) {
		double midLo = lo + (hi - lo) / 3;
		double midHi = hi - (hi - lo) / 3;

		if (maxSquare(midLo) < maxSquare(midHi)) {
			lo = midLo;
		}
		else {
			hi = midHi;
		}
	}

	fout << setprecision(7) << maxSquare(lo);

	return 0;
}
