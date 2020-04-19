#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

long n;
vector<long> d; // простые делители

// выдает первый делитель числа x не меньший i
long findDiv(long x, long i) {
	for (; i * i <= x; i++) {
		if (x % i == 0) {
			return i;
		}
	}
	return x;
}

// разбивает число на делители
void factorize(long n) {
	for (int i = findDiv(n, 2); n != 1; i = findDiv(n, i)) {
		d.push_back(i);
		while (n % i == 0) {
			n /= i;
		}
	}
}


// проверка на взаимную простоту
bool coprime(long a, long b) {
	if (a == 0 || b == 0) {
		return true;
	}
	while (b != 0) {
		a %= b;
		swap(a, b);
	}
	return a == 1;
}

long add(long n, long k, long prev);

// пытаемся домножить последнее число
// p - произведение чисел
// prev - предыдущее число в наборе
// i - индекс делителя, с которого начинать перебор
long mul(long x, long p, long k, long prev, long i) {
	if (p > n) {
		return 0;
	}

	long res = 0;
	for (; i < d.size(); i++) {
		if (!coprime(prev, d[i])) {
			continue;
		}

		long x2 = x * d[i];
		if (n % x2 != 0) {
			continue;
		}

		if (x2 > prev) {
			res += add(p * d[i], k, x2);
		}
		res += mul(x2, p * d[i], k, prev, i);
	}

	return res;
}

// пытаемся добавить число в набор
// p - произведение чисел
// prev - предыдущее число в наборе
long add(long p, long k, long prev) {
	if (p > n) {
		return 0;
	}
	if (k == 0) {
		// набор найден
		return 1;
	}
	k -= 1;

	long res = 0;
	for (int i = 0; i < d.size(); i++) {
		if (!coprime(prev, d[i])) {
			continue;
		}

		if (d[i] > prev) {
			res += add(p * d[i], k, d[i]);
		}
		res += mul(d[i], p * d[i], k, prev, i);
	}

	return res;
}

long solve(long n, long k) {
	return add(1, k, 0);
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	long k;
	fin >> n >> k;

	factorize(n);
	long ans = solve(n, k) + solve(n, k - 1); // второе слагаемое для наборов, начинающихся с единицы

	fout << ans << endl;
}