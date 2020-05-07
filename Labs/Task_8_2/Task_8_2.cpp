/*
8.2. Простые примеры на перестановки (6)
Составить программы для решения следующих задач:
	1) решить уравнение на перестановках вида A ´ X = B, где A и B - заданные перестановки, а X - неизвестная перестановка;
	2) по заданной перестановке из N элементов выдать K следующих перестановок в лексикографическом порядке;
	3) по заданной перестановке построить вектор инверсий, а по вектору инверсий восстановить перестановку;
	4) перечислить перестановки из N элементов путем транспозиции смежных элементов с рекурсией и без нее.
Входные данные задавать с клавиатуры, вывод результатов - на экран.

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> Permutation;

// ввод перестановки из потока
istream& operator>>(istream& in, Permutation& p) {
	for (int i = 0; i < p.size(); i++) {
		in >> p[i];
		p[i];
	}
	return in;
}

// вывод перестановки в поток
ostream& operator<<(ostream& out, vector<int> const& p) {
	for (int i = 0; i < p.size(); i++) {
		out << p[i] << ' ';
	}
	return out;
}

// инверсия перестановки
Permutation invert(Permutation const& p) {
	Permutation inv(p.size());
	for (int i = 0; i < p.size(); i++) {
		inv[p[i] - 1] = i + 1;
	}
	return inv;
}

// произведение перестановок
Permutation operator*(Permutation const& a, Permutation const& b) {
	Permutation p(a.size());
	for (int i = 0; i < a.size(); i++) {
		p[i] = b[a[i] - 1];
	}
	return p;
}

void main1() {
	int n;
	cout << "N = "; cin >> n;
	Permutation a(n), b(n);
	cout << "A = "; cin >> a;
	cout << "B = "; cin >> b;

	auto x = invert(a) * b;
	cout << x << endl;
}

// следующая перестановка в лексикографическом порядке
void nextPermutation(Permutation& p) {
	for (int i = p.size() - 2; i >= 0; i--) {
		if (p[i] < p[i + 1]) {
			int mj = i + 1;
			for (int j = mj; j < p.size(); j++) {
				if (p[j] < p[i]) {
					continue;
				}
				if (p[j] < p[mj]) {
					mj = j;
				}
			}
			swap(p[i], p[mj]);
			reverse(p.begin() + i + 1, p.end());
			return;
		}
	}

	reverse(p.begin(), p.end());
}

void main2() {
	int n, k;
	cout << "N = "; cin >> n;
	Permutation a(n);
	cout << "A = "; cin >> a;
	cout << "K = "; cin >> k;

	for (int i = 0; i < k; i++) {
		nextPermutation(a);
		cout << a << endl;
	}
}

// получение вектора инверсий из перестановки
vector<int> inversionVector(Permutation const& p) {
	vector<int> v(p.size());
	for (int i = 1; i < p.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (p[j] > p[i]) {
				v[i]++;
			}
		}
	}
	return v;
}

// получение перестановки из вектора инверсий
Permutation permutationFromInversionVector(vector<int> const& v) {
	vector<int> numbers;
	for (int i = 1; i <= v.size(); i++) {
		numbers.push_back(i);
	}

	Permutation p(v.size());
	for (int i = v.size() - 1; i >= 0; i--) {
		auto it = numbers.end() - 1 - v[i];
		p[i] = *it;
		numbers.erase(it, it + 1);
	}

	return p;
}

void main3() {
	int n;
	cout << "N = "; cin >> n;
	Permutation a(n);
	cout << "A = "; cin >> a;

	auto v = inversionVector(a);
	cout << "V = " << v << endl;

	a = permutationFromInversionVector(v);
	cout << "A = "; cout << a << endl;
}

// получение всех перестановок путем транспозиции соседних элементов
vector<Permutation> allPermutations(int n) {
	vector<Permutation> permutations{ {1} };

	for (int m = 2; m <= n; m++) {
		vector<Permutation> newPermutations;
		newPermutations.reserve(permutations.size() * m);
		for (int i = 0; i < permutations.size(); i++) {
			for (int j = 0; j < m; j++) {
				auto p = permutations[i];
				if (i % 2) {
					p.insert(p.begin() + j, m);
				}
				else {
					p.insert(p.end() - j, m);
				}
				newPermutations.push_back(move(p));
			}
		}
		permutations = move(newPermutations);
	}

	return permutations;
}

void allPermutationsRecursiveImpl(int n, int m, int i, Permutation const& currentPermutation, vector<Permutation>& permutations) {
	if (m > n) {
		permutations.push_back(currentPermutation);
		return;
	}

	for (int j = 0; j < m; j++) {
		auto p = currentPermutation;
		if (i % 2) {
			p.insert(p.begin() + j, m);
		}
		else {
			p.insert(p.end() - j, m);
		}
		allPermutationsRecursiveImpl(n, m + 1, i * m + j, p, permutations);
	}
}

// получение всех перестановок путем транспозиции соседних элементов рекурсивным способом
vector<Permutation> allPermutationsRecursive(int n) {
	vector<Permutation> permutations;

	allPermutationsRecursiveImpl(n, 2, 0, { 1 }, permutations);

	return permutations;
}

void main4() {
	int n;
	cout << "N = "; cin >> n;

	cout << "1 - без рекурсии\n";
	cout << "2 - с рекурсией\n";
	int m;
	cout << "> ";  cin >> m;

	vector<Permutation> v;
	if (m == 1) {
		v = allPermutations(n);
	}
	else if (m == 2) {
		v = allPermutationsRecursive(n);
	}
	else {
		return;
	}

	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
}

void printMenu() {
	cout << "0 - выход\n";
	cout << "1 - A * X = B\n";
	cout << "2 - K следующих перестановок\n";
	cout << "3 - вектор инверсий\n";
	cout << "4 - перестановки путем транспозиций\n";
	cout << "> ";
}

int main() {
	while (true) {
		printMenu();

		int n;
		cin >> n;
		switch (n) {
		case 1:
			main1();
			break;
		case 2:
			main2();
			break;
		case 3:
			main3();
			break;
		case 4:
			main4();
			break;
		case 0:
			return 0;
		}
	}
}
