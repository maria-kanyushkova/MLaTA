﻿/*
13.8. Имена (8)
На далекой планете Тау Кита есть непонятные нам обычаи. Например, таукитяне очень необычно для землян выбирают имена своим детям. Родители так выбирают имя ребенку, чтобы оно могло быть получено как удалением некоторого набора букв из имени отца, так и удалением некоторого набора букв из имени матери. Например, если отца зовут «abacaba», а мать — «bbccaa», то их ребенок может носить имена «a», «bba», «bcaa», но не может носить имена «aaa», «ab» или «bbc». Возможно, что имя ребенка совпадает с именем отца и/или матери, если оно может быть получено из имени другого родителя удалением нескольких (возможно, ни одной) букв.
Пусть отец по имени X и мать по имени Y выбирают имя своему новорожденному ребенку. Так как в таукитянских школах учеников часто вызывают к доске в лексикографическом порядке имен учеников, то есть в порядке следования имен в словаре, то они хотят выбрать своему ребенку такое имя, чтобы оно лексикографически следовало как можно позже.
Формально, строка S лексикографически больше строки T, если выполняется одно из двух условий:
	- строка T получается из S удалением одной или более букв с конца строки S;
	- первые (i - 1) символов строк T и S не различаются, а буква в i-й позиции строки T следует в алфавите раньше буквы в i-й позиции строки S.
Требуется написать программу, которая по именам отца и матери находит лексикографически наибольшее имя для их ребенка.
Ввод. 
Первая строка входного файла INPUT.TXT содержит отца X. Вторая строка входного файла содержит имя матери Y. Каждое имя состоит из строчных букв латинского алфавита, включает хотя бы одну букву и имеет длину не более 105 букв.
Следующие N строк содержат два целых числа X и Y (0 £ X, Y £ 6), разделенные пробелом.
Вывод.
Выходной файл OUTPUT.TXT должен содержать искомое лексикографически наибольшее из возможных имен ребенка. В случае, если подходящего имени для ребенка не существует, выходной файл должен быть пустым.

Примеры
Ввод 1    Ввод 2
abcabca   ccba
abcda     accbbaa
Вывод 1   Вывод 2
ca        ccba

Пояснения к примеру. В первом примере имя ребенка не может начинаться с буквы большей с, так как имя отца не содержит таких букв. Буква с содержится в обоих именах, следовательно, имя ребенка может начинаться с этой буквы. Единственная буква, которая может идти следом за буквой с в имени ребенка — это буква a.

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	string a, b;
	fin >> a >> b;

	vector<int> na(26), nb(26);
	for (auto c : a) {
		na[c - 'a']++;
	}
	for (auto c : b) {
		nb[c - 'a']++;
	}

	string ans;
	int ai = 0, bi = 0;
	for (char c = 'z'; c >= 'a'; c--) {
		int i = c - 'a';
		int n = min(na[i], nb[i]);
		ans.append(n, c);

		int x = na[i] - n;
		while (na[i] != x) {
			na[a[ai] - 'a']--;
			ai++;
		}

		x = nb[i] - n;
		while (nb[i] != x) {
			nb[b[bi] - 'a']--;
			bi++;
		}
	}

	fout << ans << endl;

	return 0;
}