#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Position {
    int i, j;
};

const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, 1, 0, -1};

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, k;
    fin >> n >> k;

    vector <vector<char>> a(n + 2, vector<char>(k + 2, 0));
    for (int i = 0; i < n; i++) {
        string s;
        fin >> s;
        for (int j = 0; j < k; j++) {
            a[i + 1][j + 1] = s[j] - '0';
        }
    }

    queue <Position> q;
    q.push({0, 0});
    a[0][0] = 2;

    while (!q.empty()) {
        auto pos = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            Position pos2 = pos;
            pos2.i += di[d];
            pos2.j += dj[d];

            if (pos2.i < 0 || pos2.j < 0 || pos2.i >= n + 2 || pos2.j >= k + 2) {
                continue;
            }
            if (a[pos2.i][pos2.j] != 0) {
                continue;
            }

            a[pos2.i][pos2.j] = 2;
            q.push(pos2);
        }
    }

    int ans = 0;
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < k + 1; j++) {
            for (int d = 0; d < 4; d++) {
                if (a[i][j] == 1 && a[i + di[d]][j + dj[d]] == 2) {
                    ans++;
                }
            }
        }
    }

    fout << ans << endl;
}

