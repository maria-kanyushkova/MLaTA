﻿/*
20.3. Король (4)
В некоторой клетке доски N´N (1 £ N £ 100000) стоит король. Горизонтали и вертикали доски нумеруются с 1 снизу вверх и слева направо. Координаты клетки определяются как (P, Q), где P – номер строки, а Q – номер столбца. Двое по очереди двигают короля. Разрешается двигать короля только вниз, влево или по диагонали вниз влево. Цель игры – задвинуть короля в угол, то есть в клетку с координатами (1, 1). Требуется написать программу, которая по заданным координатам клетки найдет номер игрока, выигрывающего при правильной игре. Считается, что первый номер имеет игрок, начинающий игру.
Ввод из файла INPUT.TXT. В первой строке задано число заданных вариантов M (1 £ M £ 5) через пробел. В каждой из следующих M строк - по два целых числа от 1 до N через пробел, задающих номера строки и столбца соответственно, т.е. координаты клеток доски.
Вывод в файл OUTPUT.TXT. Выдается M строк. В каждой из них указывается номер игрока (1 или 2), который выигрывает при правильной игре.
Пример
Ввод
2
1 2
3 1
Вывод
1
2

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <fstream>

using namespace std;

// Выигрышная стретегия:
// Если хотя бы одна координата четная, то нужно делать ход, переводящий фигуру на позицию с нечетными координатами.
// В такой случае противник будет вынужден делать ход, переводящий фигуру в позицию с хотя бы одной четной координатой.
// Т.к. позиция (1, 1) проигрышая, а сумма координат уменьшается, то рано или поздно противник проиграет
int winner(int x, int y) {
	if ((x % 2) && (y % 2)) {
		return 2;
	}
	else {
		return 1;
	}
}


int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int m;
	fin >> m;
	for (int i = 0; i < m; i++) {
		int x, y;
		fin >> x >> y;
		fout << winner(x, y) << endl;
	}
}