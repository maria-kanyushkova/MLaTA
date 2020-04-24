/*
14.11. Буйки (9)
На пляже перпендикулярно береговой линии размечены прямолинейными буйками
параллельные плавательные дорожки. Они получились разной ширины. Требуется сдвинуть
некоторые из буйков без изменения порядка их следования так, чтобы дорожки оказались равной
ширины, а сумма сдвигов была минимальной.
Ввод. 
Первая строка содержит число буйков N (2 ≤ N ≤ 400). Во второй строке указываются
координаты буйков X 1 &lt; X 2 &lt;…&lt; X N (-10000 ≤ X i ≤ 10000) в виде целых чисел по оси X,
совпадающей с береговой линией.
Вывод. 
В первой строке выводится с точностью до 4 знаков действительное число S –
минимальная общая длина требуемых сдвигов. Во второй строке выводятся через пробел с
точностью до 7 знаков новые координаты буйков. Если имеется несколько вариантов решения,
вывести любое из них.
Пример
Ввод
4
-2 2 6 9
Вывод
1.0000
-2.00000 1.6666667 5.3333333 9.0000000

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const double eps = 1e-8;

int n;
vector<double> x;

// вычисляет общую сумму сдвигов по заданным ширине дорожек и координате левого буйка
double dist(double w, double l) {
	double res = 0;
	for (int i = 0; i < n; i++) {
		res += abs(x[i] - l - w * i);
	}
	return res;
}

// находит оптимальную координату левого буйка по заданной ширине дорожек
double left(double w) {
	double l = min(x[0], x.back() - w * (n - 1));
	double r = x.back();

	while (r - l > eps) {
		double d = (r - l) / 3;
		double ml = l + d;
		double mr = r - d;

		if (dist(w, ml) > dist(w, mr)) {
			l = ml;
		}
		else {
			r = mr;
		}
	}

	return l;
}

// вычисляет минимальную сумму сдвигов по заданной ширине дорожек
double distLeft(double w) {
	return dist(w, left(w));
}

// находит оптимальную ширину дорожек
double width() {
	double l = 0;
	double r = 0;
	for (int i = 1; i < n; i++) {
		r = max(r, abs(x[i] - x[i - 1]));
	}

	while (r - l > eps) {
		double d = (r - l) / 3;
		double ml = l + d;
		double mr = r - d;

		if (distLeft(ml) > distLeft(mr)) {
			l = ml;
		}
		else {
			r = mr;
		}
	}

	return l;
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	fin >> n;
	x.resize(n);
	for (int i = 0; i < n; i++) {
		fin >> x[i];
	}

	double w = width();
	double l = left(w);

	fout << setprecision(12) << setiosflags(ios::fixed);

	fout << dist(w, l) << endl;
	for (int i = 0; i < n; i++) {
		fout << l + w * i << ' ';
	}
	fout << endl;

	return 0;
}