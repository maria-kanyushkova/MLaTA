/*
11.9. Выпуклая оболочка (7)
Найти выпуклую оболочку множества точек методом Грэхема.

Ввод из файла INPUT.TXT. В первой строке находится число N (1 ≤ N ≤ 10 5 ), задающее
количество точек. Следующие N строк содержат пары целых чисел - координаты точек (X i , Y i ).

Вывод в файл OUTPUT.TXT. В первой строке выводится M – количество вершин минимальной
оболочки. Следующие N строк содержат пары целых чисел - координаты вершин (X i , Y i ) в порядке
обхода против часовой стрелки, начиная от самой левой из самых нижних вершин.

Ограничения: координаты целые и по модулю не превосходят 10000, время 1 с.

Примеры
Ввод
6
0 0
2 2
2 0
0 2
1 1
1 0

Вывод
4
0 0
2 0
2 2
0 2

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct point {
    double x;
    double y;
};

enum index {
    ZERO = 0,
    ONE
};

using points_t = vector<point>;

const double EPS = 10e-5;
const double MAX = 100000;
point MIN_POINT{MAX + ONE, MAX + ONE};

double cos(point point) {
    return point.x / sqrt(point.x * point.x + point.y * point.y);
}

double getZCoordinate(point a, point b, point c) {
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}

double length(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    size_t size;
    input >> size;

    points_t points{};
	point pointBuffer{};
	size_t k = 0;
	size_t i = 0;
	while (input >> pointBuffer.x >> pointBuffer.y) {
		if (pointBuffer.y <= MIN_POINT.y) {
			if (pointBuffer.y < MIN_POINT.y) {
				k = i;
				MIN_POINT.y = pointBuffer.y;
				MIN_POINT.x = pointBuffer.x;
			} else if (pointBuffer.x < MIN_POINT.x) {
				k = i;
				MIN_POINT.x = pointBuffer.x;
			}
		}
		points.push_back(pointBuffer);
		i++;
	}
	swap(points[ZERO], points[k]);

    sort(points.begin() + ONE, points.end(), [](point const &a, point const &b) {
        auto z = getZCoordinate(MIN_POINT, a, b);
        if (a.x == b.x && a.y == b.y) {
            return true;
        };
        if (abs(z) < EPS) {
            return length(MIN_POINT, a) < length(MIN_POINT, b);
        }
        return z >= ZERO;
    });

    points_t stack{};

    stack.push_back(points[ZERO]);
    stack.push_back(points[ONE]);

    double zCoord = ZERO;
    size_t last = ONE;
    for (size_t i = last + 1; i < size; ++i) {
		zCoord = getZCoordinate(stack[last - 1], stack[last], points[i]);
        auto lastMoreZero = last > ZERO;
        auto zLessZero = zCoord < ZERO;
        auto absZLessEps = abs(zCoord) < EPS;
        while (lastMoreZero && (zLessZero || absZLessEps)) {
            stack.pop_back();
            --last;
            if (last == ZERO) {
                break;
            }
			zCoord = getZCoordinate(stack[last - 1], stack[last], points[i]);
			lastMoreZero = last > ZERO;
			zLessZero = zCoord < ZERO;
			absZLessEps = abs(zCoord) < EPS;
        }
        stack.push_back(points[i]);
        ++last;
    }

	auto sizeBuffer = stack.size();
	output << to_string(sizeBuffer) << endl;
	for (size_t i = ZERO; i < stack.size(); ++i) {
		output << stack[i].x << ' ' << stack[i].y << endl;
	}
}
