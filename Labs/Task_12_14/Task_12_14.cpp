/*
12.14. Максимальный путь 2 (8)
Имеется взвешенный ориентированный ациклический граф. Найти максимальный путь, используя топологическую сортировку.
Ввод из файла INPUT.TXT. 
Первая строка входного файла INPUT.TXT содержит 4 числа: N - количество вершин графа (3 ≤ N ≤ 2000), M – дуг (3 ≤ M ≤ 2000000), A – номер начальной вершины и B – номер конечной вершины. В следующих M строках по 3 числа, задающих дуги: начало дуги, конец дуги, длина (вес).
Вывод в файл OUTPUT.TXT. 
В первую строку вывести максимальную длину пути, во вторую строку через пробел – вершины максимального пути. Если решений несколько, вывести любое из них. Если пути нет, выдать No.
Пример
Ввод
4 5 1 3
1 2 5
1 4 7
2 3 4
4 2 2
4 3 3
Вывод
13
1 4 2 3

источник топологической сортировки https://e-maxx.ru/algo/topological_sort

Visual Studio 2019
Канюшкова Мария ПС-21
*/

#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const long MIN_COST = -1e9;

struct Edge {
	int to; // вершина, в которую направлено ребро
	int w; // вес
};

int n, m, a, b;
vector<vector<Edge>> graph;

void readGraph(istream& in) {
	in >> n >> m >> a >> b;
	a--;
	b--;

	graph.resize(n);
	for (int i = 0; i < m; i++) {
		Edge e;
		int from;
		in >> from >> e.to >> e.w;
		from--;
		e.to--;
		graph[from].push_back(e);
	}
}

vector<int> order; // порядок вершин после топологической сортировки
vector<bool> visited;
vector<long> cost; // расстояния от вершин до конечной вершины
vector<int> from; // вершины, через которые идут максимальные пути

void dfs(int i) {
	if (visited[i]) {
		return;
	}

	visited[i] = true;
	for (auto& e : graph[i]) {
		dfs(e.to);
		if (cost[e.to] != MIN_COST) {
			long newCost = cost[e.to] + e.w;
			if (newCost > cost[i]) {
				cost[i] = newCost;
				from[i] = e.to;
			}
		}
	}

	order.push_back(i);
}

void solve() {
	order.reserve(n);
	visited.resize(n, false);
	cost.resize(n, MIN_COST);
	from.resize(n, -1);
	cost[b] = 0;

	for (int i = 0; i < n; i++) {
		dfs(i);
	}

	reverse(order.begin(), order.end());
}

void printAns(ostream& out) {
	if (from[a] == -1) {
		out << "No\n";
		return;
	}

	vector<int> path;
	for (int i = a; i != -1; i = from[i]) {
		path.push_back(i);
	}

	out << cost[a] << '\n';
	for (auto i : path) {
		out << i + 1 << ' ';
	}
	out << '\n';
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	readGraph(fin);
	solve();
	printAns(fout);

	return 0;
}

