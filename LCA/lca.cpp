#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int N = 100007;

int n, t, vis[N], table[N][30];
vector<int> edges[N];

void dfs(int u, int par = -1) {
	vis[u] = ++t;

	if(par == -1) par = u;
	table[u][0] = par;
	for(int i = 1; i < 30; ++i)
		table[u][i] = table[table[u][i-1]][i-1];

	for(int i = 0; i < edges[u].size(); ++i) {
		int v = edges[u][i];
		if(v == par) continue;
		dfs(v, u);
	}
}

int lca(int u, int v) {
	if(u == v) return u;
	if(vis[u] > vis[v]) swap(u, v);

	for(int i = 29; i >= 0; --i)
		if(vis[table[v][i]] > vis[u]) v = table[v][i];

	return table[v][0];
}

int main() {
	int m;
	cin >> n >> m;

	for(int i = 0; i < n-1; ++i) {
		int u, v;
		cin >> u >> v;
		edges[u].pb(v);
		edges[v].pb(u);
	}

	dfs(1);

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		cout << lca(u, v) << endl;
	}

}