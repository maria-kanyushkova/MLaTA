/*
8.3. Матрица (8)
В матрице A размера NN числа от 1 до N 2 . Каждое число записано ровно один раз. Даны две
матрицы размера N  N: Top и Left. Значение Top i j определяет количество чисел, больших A i j и
расположенных выше по столбцу, Left i j - количество чисел, больших A i j и расположенных левее по
строке. Найти возможные значения матрицы A. Если решений несколько, вывести любое.
Ввод из файла INPUT.TXT. В первой строке N (1 ≤ N ≤100), затем N строк матрицы Top (числа
через пробел), затем N строк матрицы Left. Числа в обеих матрицах от 0 до N.
Вывод в файл OUTPUT.TXT матрицы A – N строк, числа в строке через пробел. Если решений
нет, вывести 0.

Пример
Ввод
3
0 0 0
0 0 0
0 0 2
0 0 0
0 1 0
0 1 2

Вывод
1 2 6
5 3 7
9 8 4

Канюшкова Мария ПС-21
Visual Studio 2019
*/

#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>

#define DEBUG_VALUE false

using namespace std;

struct matrix {
    size_t matrixSize;
	vector<vector<int>> matrixData;

    matrix(size_t size) : matrixSize(size) {
		matrixData = vector<vector<int>>(size, vector<int>(size, 0));
    }

    vector<int> &operator[](size_t index) {
        return matrixData[index];
    }
};

int main() {
    try {
        ifstream input("input1.txt");
        ofstream output("output.txt");
        size_t size = 0;
        input >> size;
        matrix matrixTop(size);
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				input >> matrixTop[i][j];
			}
		}
        matrix matrixLeft(size);
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				input >> matrixLeft[i][j];
			}
		}
        matrix matrixMain(size);
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				input >> matrixMain[i][j];
			}
		}

        bool error = false;

        for (size_t i = 0; i < matrixTop.matrixSize; ++i) {
            for (size_t j = 0; j < matrixTop.matrixSize; ++j) {
                if (static_cast<size_t>(matrixTop[i][j]) > i || static_cast<size_t>(matrixLeft[i][j]) > j) {
                    error = true;
                    break;
                }
            }
            if (error) { break; }
        }

        if (!error) {
            for (size_t i = 0; i <= size * size; ++i) {
                auto current = static_cast<int>(i);
                bool result = false;
                bool flag = false;
				int x = 0;
				int z = 0;
				int free = 0;
                for (size_t j = 0; j < matrixMain.matrixSize; ++j) {
                    for (size_t m = 0; m < matrixMain.matrixSize; ++m) {
                        if (!matrixMain[j][m] == 0) { continue; }
                        ++z;
                        x = 0;
                        for (size_t k = 0; k < j; ++k) {
                            x += matrixMain[k][m] == 0 ? 1 : 0;
                        }
                        flag = !(matrixTop[j][m] == 0 && x > 0 || x > matrixTop[j][m]);
                        if (flag) {
                            for (auto k = j; k < matrixMain.matrixSize; ++k) {
                                const auto isTopZero = matrixTop[k][m] == 0;
                                const auto isMainZero = matrixMain[k][m] == 0;
                                const auto left = isTopZero && current > matrixMain[k][m] && !isMainZero;
                                const auto right = !isTopZero && x <= matrixTop[k][m] && j != k && isMainZero;
                                if (left || right) {
                                    flag = false;
                                    break;
                                }
                                if (matrixMain[k][m] == 0) { ++x; }
                            }
                        }
                        free = z - 1;
                        flag = matrixLeft[j][m] == 0 && free > 0 || free > matrixLeft[j][m] ? false : flag;
                        if (flag) {
                            for (auto k = m; k < matrixMain.matrixSize; ++k) {
                                const auto isLeftZero = matrixLeft[j][k] == 0;
                                const auto isMainZero = matrixMain[j][k] == 0;
                                const auto left = isLeftZero && current > matrixMain[j][k] && !isMainZero;
                                const auto right = !isLeftZero && free <= matrixLeft[j][k] && k != m && isMainZero;
                                if (left || right) {
                                    flag = false;
                                    break;
                                }
                                if (matrixMain[j][k] == 0) { ++free; }
                            }
                        }
                        if (flag) {
							matrixMain[j][m] = current;
                            result = true;
                            break;
                        }
                    }
                    if (result) { break; }
                    z = 0;
                }
                if (!result) { 
					error = true;
					break;
				}
            }
        }

        if (error) {
            output << 0 << endl;
            if (DEBUG_VALUE) {
                cout << 0 << endl;
            }
        } else {
			for (size_t i = 0; i < matrixMain.matrixSize; ++i) {
				for (size_t j = 0; j < matrixMain.matrixSize; ++j) {
					output << matrixMain[i][j] << ' ';
					if (DEBUG_VALUE) {
						cout << matrixMain[i][j] << ' ';
					}
				}
				output << endl;
				if (DEBUG_VALUE) {
					cout << endl;
				}
			}
        }
    }
    catch (exception &ex) {
        cerr << ex.what() << endl;
    }
}
