#include <bits/stdc++.h>

#define pb push_back
using namespace std;
typedef long long ll;

const int N = 2007;

int match[N], umatch[N], vis[N];
vector<int> e[N];

int dfs(int u) {
	vis[u] = 1;
	for(int v : e[u]) {
		if(match[v] == 0 or (!vis[match[v]] and dfs(match[v]))) {
			match[v] = u;
			umatch[u] = v;
			return 1;
		}
	}
	return 0;
}

int kuhn(int n) {
	int flow = 0;
	int flag = 0;
	do {
		flag = 0;
		memset(vis, 0, sizeof vis);
		for(int u = 1; u <= n; ++u) {
			if(!umatch[u] and !vis[u] and dfs(u)) flow += (flag = 1);
		}
	} while(flag);
	return flow;
}

int id[N][N];

ll solve(ll n, ll m) {

	int us = 0, vs = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if((j + i)&1) {
				id[i][j] = ++vs;
			} else {
				id[i][j] = ++us;
			}
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if((i + j)&1) continue;
			int moves[][2] = {{-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, -1}, {-2, 1}, {0, 3}, {0, -3}, {-3, 0}, {3, 0}};
			for(int k = 0; k < 12; ++k) {
				int p = i + moves[k][0];
				int q = j + moves[k][1];
				if(p >= 0 and p < n and q >= 0 and q < m) {
					e[id[i][j]].pb(id[p][q]);
				}
			}
		}
	}

	return 2ll * kuhn(us);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	ll n, m; cin >> n >> m;
	if(n > m) swap(n, m);
	if(n == 1) {
		ll tot = m%6;
		cout << 6 * (m/6) + 2 * max(0ll, tot - 3) << endl;
	} else if(n * m <= 2000) {
		cout << solve(n, m) << endl;
	} else {
		cout << n * m - ((n * m)&1) << endl;
	}
}