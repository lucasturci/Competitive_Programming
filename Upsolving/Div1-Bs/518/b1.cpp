#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define eb emplace_back

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 200007;
void no() {
	cout << "No\n";
	exit(0);
}

void yes() {
	cout << "Yes\n";
	exit(0);
}

vector<int> e[N];
int lev[N], pai[N];
int n, k;

void dfs(int u, int p = -1, int l = 0) {
	pai[u] = p;
	lev[u] = l;
	for(int v : e[u]) {
		if(v == p) continue;
		dfs(v, u, l+1);
	}
}

void solve(int u, int p = -1, int l = 0) {
	int d = 0;
	for(int v : e[u]) {
		if(v == p) continue;
		solve(v, u, l+1);
		d ++;
	}

	if(l < k) {
		if(d < 3) no();
	} else if(l == k) {
		if(d) no();
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;

	for(int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		e[u].pb(v);
		e[v].pb(u);
	}

	dfs(1);

	int r = 1;
	for(int i = 1; i <= n; ++i) {
		if(lev[i] > lev[r]) r = i;
	}

	dfs(r);
	int s = 1;
	for(int i = 1; i <= n; ++i) {
		if(lev[i] > lev[s]) s = i;
	}

	vector<int> path;
	for(int u = s; u != -1; u = pai[u]) {
		path.pb(u);
	}

	if(path.size() != 2 * k + 1) no();
	int centro = path[k];

	solve(centro);
	yes();

}