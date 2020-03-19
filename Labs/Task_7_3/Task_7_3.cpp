/*
7.3. Прямоугольники 1(8)
На координатной плоскости задано N прямоугольников со сторонами, параллельными
координатным осям. Найти площадь фигуры, получающейся в результате объединения
прямоугольников.
Ввод из файла INPUT.TXT. В первой строке содержится значение N (1 ≤ N ≤ 500). В каждой из
следующих N строк – четыре целых числа A i , B i , C i , D i через пробел, определяющие координаты
левого верхнего и правого нижнего углов очередного прямоугольника (-10 6 ≤ A i , B i , C i , D i ≤ 10 6 ; A i
≤ C i ; B i ≥ D i ).
Вывод в файл OUTPUT.TXT единственного целого числа – площади фигуры.
Пример
Ввод
2
5 15 25 5
0 10 20 0
Вывод
325

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <fstream>

using namespace std;

struct rectangle {
    long long x1, y1, x2, y2;
};

struct segment {
    long long a, b;
};

int main() {
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");
    int count, x1, y1, x2, y2;
    vector <rectangle> rects;
	inFile >> count;
    while (count-- > 0) {
		inFile >> x1 >> y1 >> x2 >> y2;
		rects.push_back({ x1, y1, x2, y2});
    }

    vector<long long> eventsArray;
    for (auto &rect : rects) {
		eventsArray.push_back(rect.x1);
		eventsArray.push_back(rect.x2);
    }
    sort(eventsArray.begin(), eventsArray.end());
    const auto it = unique(eventsArray.begin(), eventsArray.end());
	eventsArray.resize(distance(eventsArray.begin(), it));

    long long area = 0;
    for (size_t i = 0; i < eventsArray.size() - 1; ++i) {
        const auto x = eventsArray[i];
        deque<long long> start, end;
        for (auto &rect : rects) {
            if (rect.x1 <= x && rect.x2 > x) {
                start.push_back(min(rect.y1, rect.y2));
                end.push_back(max(rect.y1, rect.y2));
            }
        }
        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        auto depth = 0;
        segment seg{};
        vector <segment> segments;
        while (!start.empty() || !end.empty()) {
            long long y = 0;
            const auto pre_depth = depth;
            if (!start.empty() && start.front() <= end.front()) {
                depth++;
                y = start.front();
                start.pop_front();
            } else {
                depth--;
                y = end.front();
                end.pop_front();
            }
            if (pre_depth == 0) {
                seg.a = y;
            } else if (depth == 0) {
                seg.b = y;
                segments.push_back(seg);
            }
        }

        const auto width = eventsArray[i + 1] - x;
        for (auto &segment : segments) {
            area += width * (segment.b - segment.a);
        }
    }
	outFile << area << endl;
}
