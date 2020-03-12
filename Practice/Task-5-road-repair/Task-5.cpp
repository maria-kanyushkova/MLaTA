#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct point {
	int x;
	int type;

	point(const int x, const int type) : x(x), type(type) {}

	point() {
		x = 0;
		type = 0;
	}
};

inline bool comp(const point a, const point b) {
	return a.x < b.x || a.x == b.x && a.type > b.type;
}

int main() {
	ifstream file("input10.txt");
	int n = 0;
	int m = 0;
	file >> n >> m;
	int res = 0;
	int count = 0;
	vector<point> points(2 * n);
	for (int j = 0; j < n; ++j) {
		int x = 0;
		int y = 0;
		file >> x >> y;
		points[2 * j] = point(x, 1);
		points[2 * j + 1] = point(y, -1);
	}
	sort(points.begin(), points.end(), comp);
	bool entered = false;
	for (auto& point : points) {
		res += point.type;
		if (res > m - 1 && !entered) {
			entered = true;
			count++;
		}
		if (res <= m - 1 && entered) {
			entered = false;
		}
	}
	cout << count << endl;
}
