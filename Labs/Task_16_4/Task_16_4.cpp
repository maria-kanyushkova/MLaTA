﻿/*
16.4. Сугробы на ЛЭП (8)
Служба электроснабжения проводит мониторинг уровня снега, лежащего на ЛЭП. Вся ЛЭП разбивается на участки опорами. Если снег падает на некоторый интервал ЛЭП, то высота снежного покрова на этом интервале увеличивается на высоту выпавшего снега. Снег также имеет тенденцию таять на некотором участке трассы в результате оттепели, однако сугробов отрицательной толщины быть не может. Энергетикам крайне важно уметь узнавать суммарную высоту снежного покрова на некоторых участках, чтобы определять вероятность обрыва проводов.
Ввод из файла INPUT.TXT. В первой строке находятся через пробел два числа: N – количество опор и M – количество команд (1 £ N, M £ 105). Команды бывают двух видов:
* 1 L R S - на участок с L-й опоры по R-ю выпало S сантиметров снега (-100 £ S £ 100);
* 2 L R – запрос о высоте снега на участке от L-й опоры по R-ю (1 £ L < R £ N).
Таяние снега показывает первый вид команды с отрицательным значением S. Опоры нумеруются от 1 до N.
Вывод в файл OUTPUT.TXT. На каждый запрос (команду второго вида) требуется выводить суммарную высоту снежного покрова, лежащего на проводах от L-й опоры по R-ю.
Пример
Ввод
11 5
1 1 10 10
1 2 6 -3
2 5 9
1 1 7 25
2 1 3
Вывод
37
67

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Дерево отрезков
struct SegmentTree {
	vector<long long> diff;
	vector<long long> sum;
	int n;

	SegmentTree(int n)
		: diff(4 * n, 0)
		, sum(4 * n, 0)
		, n(n)
	{}

	void add(int l, int r, int d, int i, int tl, int tr) {
		sum[i] += d * (r - l + 1);
		if (l == tl && r == tr) {
			diff[i] += d;
			return;
		}

		int tm = (tl + tr) / 2;
		if (r <= tm) {
			add(l, r, d, 2 * i + 1, tl, tm);
		}
		else if (l > tm) {
			add(l, r, d, 2 * i + 2, tm + 1, tr);
		}
		else {
			add(l, tm, d, 2 * i + 1, tl, tm);
			add(tm + 1, r, d, 2 * i + 2, tm + 1, tr);
		}
	}

	// Добавление на отрезке
	void add(int l, int r, int d) {
		return add(l, r, d, 0, 0, n - 1);
	}

	long long rsq(int l, int r, int i, int tl, int tr) {
		if (l == tl && r == tr) {
			return sum[i];
		}

		int tm = (tl + tr) / 2;
		long long sum = diff[i] * (r - l + 1);
		if (r <= tm) {
			sum += rsq(l, r, 2 * i + 1, tl, tm);
		}
		else if (l > tm) {
			sum += rsq(l, r, 2 * i + 2, tm + 1, tr);
		}
		else {
			sum += rsq(l, tm, 2 * i + 1, tl, tm);
			sum += rsq(tm + 1, r, 2 * i + 2, tm + 1, tr);
		}
		return sum;
	}

	// Сумма на отрезке
	long long rsq(int l, int r) {
		return rsq(l, r, 0, 0, n - 1);
	}
};

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n, m;
	fin >> n >> m;

	SegmentTree tree(n - 1);
	for (int i = 0; i < m; i++) {
		int cmd, l, r;
		fin >> cmd >> l >> r;
		l--;
		r--;
		if (cmd == 1) {
			// выпал снег
			int d;
			fin >> d;
			tree.add(l, r - 1, d);
		}
		else {
			// запрос суммы
			fout << tree.rsq(l, r - 1) << endl;
		}
	}

	return 0;
}