#include <bits/stdc++.h>
#define inf 0x3f3f3f3f

using namespace std;
typedef long long ll;

const int N = 107;

int edges[N][N], best[N][N];

int main() {
	int n, m;
	cin >> n >> m;

	for(int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		edges[u][v] = edges[v][u] = w;
		best[u][v] = best[v][u] = w;
	}

	for(int u = 1; u <= n; ++u)
		for(int v = 1; v <= n; ++v) 
			if(best[u][v] == 0 and u != v) best[u][v] = inf;

	for(int u = 1; u <= n; ++u) {
		for(int v = 1; v <= n; ++v) {
			for(int k = 1; k <= n; ++k) {
				best[u][v] = min(best[u][v], best[u][k] + best[k][v]);
			}
		}
	}

	for(int u = 1; u <= n; ++u) {
		cout << "Saindo de " << u << ":" << endl;
		for(int v = 1; v <= n; ++v) {
			cout << '\t' << v << " " << best[u][v] << endl;
		}
	}

}