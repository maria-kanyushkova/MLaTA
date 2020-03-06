// 2.2. Путь коня (6)
// Дана шахматная доска, состоящая из N  N  клеток (2 ≤ N ≤ 300), несколько из них вырезано.
// Провести ходом коня через невырезанные клетки путь минимальной длины из одной заданной
// клетки в другую.
// Ввод из файла INPUT.TXT. В первой строке задано число N. В следующих N строках
// содержится по N символов. Символом # обозначена вырезанная клетка, точкой - невырезанная
// клетка, @ - заданные клетки (таких символов два).
// Вывод в файл OUTPUT.TXT. Если путь построить невозможно, вывести &quot;Impossible&quot;, в
// противном случае вывести такую же карту, как и на входе, но пометить все промежуточные
// положения коня символом @.
// Примеры
// Ввод 1   Ввод 2   Ввод 3
// 5        5        5
// .....    @..@.    @....
// .@@..    ..##.    ..#..
// .....    .....    .#...
// .....    .....    .....
// .....    .....    ....@
// Вывод 1  Вывод 2  Вывод 3
// ...@.    @..@.    Impossible
// .@@..    ..##.
// ....@    .@..@
// .....    ..@..
// .....    @....

// Канюшкова Мария ПС-21
// Visual Studio 2019

#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Position {
    int i, j;
};

const int di[] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dj[] = {1, 2, 2, 1, -1, -2, -2, -1};

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;
    vector <string> a;
    a.reserve(n);
    for (int i = 0; i < n; i++) {
        string s;
        fin >> s;
        a.push_back(s);
    }

    Position start;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == '@') {
                start = {i, j};
            }
        }
    }

    vector <vector<int>> dist(n, vector<int>(n, 300 * 300));
    vector <vector<char>> inQ(n, vector<char>(n, false));

    queue <Position> q;
    q.push(start);
    dist[start.i][start.j] = 0;
    inQ[start.i][start.j] = true;

    while (!q.empty()) {
        Position pos = q.front();
        q.pop();
        inQ[pos.i][pos.j] = false;

        for (int d = 0; d < 8; d++) {
            Position pos2 = pos;
            pos2.i += di[d];
            pos2.j += dj[d];
            if (pos2.i < 0 || pos2.j < 0 || pos2.i >= n || pos2.j >= n) {
                continue;
            }
            if (a[pos2.i][pos2.j] == '#') {
                continue;
            }

            int dist2 = dist[pos.i][pos.j] + 1;
            if (dist2 < dist[pos2.i][pos2.j]) {
                dist[pos2.i][pos2.j] = dist2;

                if (!inQ[pos2.i][pos2.j]) {
                    q.push(pos2);
                    inQ[pos2.i][pos2.j] = true;
                }
            }
        }
    }

    Position finish;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == '@' && dist[i][j] != 0) {
                finish = {i, j};
            }
        }
    }

    if (dist[finish.i][finish.j] == 300 * 300) {
        fout << "Impossible\n";
        return 0;
    }

    Position pos = finish;

    for (int i = dist[finish.i][finish.j]; i > 0; i--) {
        a[pos.i][pos.j] = '@';

        for (int d = 0; d < 8; d++) {
            Position pos2 = pos;
            pos2.i += di[d];
            pos2.j += dj[d];
            if (pos2.i < 0 || pos2.j < 0 || pos2.i >= n || pos2.j >= n) {
                continue;
            }

            if (dist[pos2.i][pos2.j] == dist[pos.i][pos.j] - 1) {
                pos = pos2;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        fout << a[i] << endl;
    }
}
