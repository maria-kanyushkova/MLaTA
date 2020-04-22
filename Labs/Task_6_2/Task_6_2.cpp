/*
6.2. Длинное деление (7)
Заданы два целых положительных числа. Требуется найти их частное и остаток от деления.
Ввод. В первой строке файла INPUT.TXT задано делимое, во второй – делитель. Количество цифр делимого и делителя от 1 до 100.
Вывод. В первой строке файла OUTPUT.TXT вывести частное, во второй строке - остаток.
Примеры
Ввод
3456
47

Вывод
73
25

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

typedef vector<int> Number;

Number strToNum(string const& str) {
	Number result;
	for (int i = 0; i < str.length(); i++) {
		result.push_back(str[i] - '0');
	}
	return result;
}

string numToStr(Number const& num) {
	string result;
	for (int i = 0; i < num.size(); i++) {
		result.push_back(num[i] + '0');
	}
	return result;
}

// нормализуем число: убираем лидирующие нули и числа, не являющиеся цифрами
void normalize(Number& num) {
	for (int i = num.size() - 1; i > 0; i--) {
		while (num[i] < 0) {
			num[i] += 10;
			num[i - 1] -= 1;
		}
		num[i - 1] += num[i] / 10;
		num[i] %= 10;
	}
	while (num[0] > 9) {
		num.insert(num.begin(), num[0] / 10);
		num[1] %= 10;
	}
	while (num.size() > 1 && num[0] == 0) {
		num.erase(num.begin());
	}
}

// сравнение чисел
bool lessNum(Number const& a, Number const& b) {
	if (a.size() > b.size()) {
		return false;
	}
	if (a.size() < b.size()) {
		return true;
	}
	for (int i = 0; i < a.size(); i++) {
		if (a[i] < b[i]) {
			return true;
		}
		if (a[i] > b[i]) {
			return false;
		}
	}
	return false;
}

// умножение на 10
void mul10(Number& num) {
	num.push_back(0);
}

// добавление единицы
void add1(Number& num) {
	num.back()++;
	normalize(num);
}

// вычитаение
void sub(Number& a, Number const& b) {
	int d = a.size() - b.size();
	for (int i = 0; i < b.size(); i++) {
		a[d + i] -= b[i];
	}
	normalize(a);
}

// сложение
void add(Number& a, Number const& b) {
	if (a.size() <= b.size()) {
		Number x(b.size() - a.size() + 1, 0);
		a.insert(a.begin(), x.begin(), x.end());
	}
	int d = a.size() - b.size();
	for (int i = 0; i < b.size(); i++) {
		a[d + i] += b[i];
	}
	normalize(a);
}

struct Result {
	Number div; // частное
	Number quo; // остаток
};

// деление почти методом столбика
Result div(Number a, Number const& b) {
	Number result = { 0 };
	while (lessNum(b, a)) {
		Number c = b;
		Number d = c;
		mul10(d);

		Number mult = { 1 };
		while (lessNum(d, a)) {
			c = d;
			mul10(d);
			mul10(mult);
		}

		sub(a, c);
		add(result, mult);
	}

	return { result, a };
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	string as, bs;
	fin >> as >> bs;
	Number a = strToNum(as);
	Number b = strToNum(bs);

	Result res = div(a, b);

	fout << numToStr(res.div) << endl;
	fout << numToStr(res.quo) << endl;

	return 0;
}

