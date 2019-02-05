/* Complexidade: O(V^2 E) */

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

const int N = 1000007, inf = 0x3f3f3f3f;

int n, m, s, t, cur = 0;
struct ed {
	int v, cap, f;
};

ed arestas[N];
vector<int> edges[N];
int ptr[N], d[N];

void add_edge(int u, int v, int cap) {
	arestas[cur] = {v, cap, 0};
	edges[u].pb(cur);
	cur++;

	arestas[cur] = {u, cap, cap};
	edges[v].pb(cur);
	cur++;
}

int bfs() {
	int i, p, u, v;
	queue<int> q;
	memset(d, inf, sizeof d);

	q.push(s);
	d[s] = 0;

	while(q.size()) {
		u = q.front();
		q.pop();

		for(i = 0; i < edges[u].size(); ++i) {
			p = edges[u][i];
			v = arestas[p].v;
			
			if(d[v] == inf and arestas[p].f < arestas[p].cap) {
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
	return d[t] != inf;
}

int dfs(int u, int f) {
	if(f == 0) return 0;
	if(u == t) return f;
	
	int v, p;
	for(int& i = ptr[u]; i < edges[u].size(); ++i) {
		p = edges[u][i];
		v = arestas[p].v;
		if(d[v] == d[u] + 1) { //esta no layered graph
			int tot = dfs(v, min(f, arestas[p].cap - arestas[p].f));
			if(tot) {
				arestas[p].f += tot;
				arestas[p^1].f -= tot;
				return tot;
			}
		}
	}

	return 0;
}

int flow() {
	int f = 0;

	while(bfs()) {
		memset(ptr, 0, sizeof ptr);
		while(int tot = dfs(s, inf)) f += tot; 
	}

	return f;
}

int main() {
	ios::sync_with_stdio(false);
	int u, v, cap;

	cin >> n >> m >> s >> t;

	for(int i = 0; i < m; ++i) {
		cin >> u >> v >> cap;
		add_edge(u, v, cap);
	}

	cout << flow() << endl;
	
}