#include <bits/stdc++.h>

#define pb push_back
using namespace std;
typedef long long ll;
const int N = 100007;
vector<int> e[N];

ll f[N];
ll ans[N];
int m;

void solve(int u, int p = -1) {

	f[u] = 1;
	for(int v : e[u]) {
		if(v == p) continue;
		solve(v, u);

		f[u] = f[u] * f[v] % m;
	}

	f[u] = (f[u] + 1)%m;
}

void dfs(int u, int p = -1) {

	if(p != -1) { // adiciona f do pai
		f[u] = (f[u] - 1 + m)%m;
		f[u] = f[u] * f[p] % m;
		f[u] = (f[u] + 1)%m;
	}

	ans[u] = (f[u] - 1 + m)%m;

	vector<ll> suf(e[u].size() + 1, 1);
	for(int i = e[u].size()-1; i >= 0; --i) {
		suf[i] = suf[i+1] * f[e[u][i]] % m;
	}

	ll aux = 1;
	for(int i = 0; i < e[u].size(); i++) {
		int v = e[u][i];

		ll valor = f[v]; // valor antes de mudar, pra nao precisar remover o pai
		if(v != p) {
			// remove v
			f[u] = aux * suf[i + 1] % m;
			f[u] = (f[u] + 1)%m; 

			dfs(v, u);	
		}
		
		aux = aux * valor % m;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n; cin >> n >> m;

	for(int i = 0; i + 1 < n; i++) {
		int u, v; cin >> u >> v;
		e[u].pb(v);
		e[v].pb(u);
	}

	solve(1, -1);
	dfs(1, -1);

	for(int i = 1; i <= n; i++) {
		cout << ans[i] << '\n';
	}
}
