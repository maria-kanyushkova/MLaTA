/*
11.9. Выпуклая оболочка (7)
Найти выпуклую оболочку множества точек методом Грэхема.
Ввод из файла INPUT.TXT. В первой строке находится число N (1 ≤ N ≤ 10 5 ), задающее
количество точек. Следующие N строк содержат пары целых чисел - координаты точек (X i , Y i ).
Вывод в файл OUTPUT.TXT. В первой строке выводится M – количество вершин минимальной
оболочки. Следующие N строк содержат пары целых чисел - координаты вершин (X i , Y i ) в порядке
обхода против часовой стрелки, начиная от самой левой из самых нижних вершин.
Ограничения: координаты целые и по модулю не превосходят 10000, время 1 с.

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
point INITIAL_MIN_POINT{MAX + ONE, MAX + ONE};

double cos(point point) {
    return point.x / sqrt(point.x * point.x + point.y * point.y);
}

double get_z(point a, point b, point c) {
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
		if (pointBuffer.y <= INITIAL_MIN_POINT.y) {
			if (pointBuffer.y < INITIAL_MIN_POINT.y) {
				k = i;
				INITIAL_MIN_POINT.y = pointBuffer.y;
				INITIAL_MIN_POINT.x = pointBuffer.x;
			}
			else if (pointBuffer.x < INITIAL_MIN_POINT.x) {
				k = i;
				INITIAL_MIN_POINT.x = pointBuffer.x;
			}
		}
		points.push_back(pointBuffer);
		i++;
	}
	swap(points[ZERO], points[k]);

    sort(points.begin() + ONE, points.end(), [](point const &a, point const &b) {
        auto z = get_z(INITIAL_MIN_POINT, a, b);
        const auto eql_points = a.x == b.x && a.y == b.y;
        if (eql_points) {
            return true;
        };
        const auto abs_z_less_eps = abs(z) < EPS;
        if (abs_z_less_eps) {
            return length(INITIAL_MIN_POINT, a) < length(INITIAL_MIN_POINT, b);
        }
        return z >= ZERO;
    });

    points_t stack{};

    stack.push_back(points[ZERO]);
    stack.push_back(points[ONE]);

    double z = ZERO;
    size_t last = ONE;
    for (size_t i = last + 1; i < size; ++i) {
        z = get_z(stack[last - 1], stack[last], points[i]);
        auto last_more_zero = last > ZERO;
        auto z_less_zero = z < ZERO;
        auto abs_z_less_eps = abs(z) < EPS;
        while (last_more_zero && (z_less_zero || abs_z_less_eps)) {
            stack.pop_back();
            --last;
            if (last == ZERO) {
                break;
            }
            z = get_z(stack[last - 1], stack[last], points[i]);
            last_more_zero = last > ZERO;
            z_less_zero = z < ZERO;
            abs_z_less_eps = abs(z) < EPS;
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
