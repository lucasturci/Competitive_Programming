#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define eb emplace_back

const int N = 1000007, inf = 0x3f3f3f3f;

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int L, R, n;
bool morto[N];
int sz[N];
vector<int> e[N];

ll ans = 0;

// o primeiro bit setado fala quantos pra tras ele vai guardar a soma
struct Bit {
	vector<int> b;

	Bit(){}
	Bit(int n) {
		b.assign(n + 1, 0);
	}

	// soma val
	void update(int p, int val) {
		for(++p; p < b.size(); p += p&(-p)) 
			b[p] += val;
	}


	// 1010 & 0110
	// 0000
	// 0001 V | | |
	// 0010   V | |
	// 0011 V   | |
	// 0100     V |
	// 0101 V |   |
	// 0110   V   |
	// 0111 V     |
	// 1000       V
	// 1001 V | |
	// 1010   V |
	// 1011 V   |
	// 1100     V
	// 1101 V |
	// 1110   V
	// 1111 V  

	int query(int p) {
		int ans = 0;
		p = min(p, (int) b.size()-2);
		for(++p; p > 0; p -= p&(-p)) 
			ans += b[p];
		return ans;
	}

	int query(int l, int r) {
		assert(r >= l);
		return query(r) - query(l - 1);
	}
};

Bit bit;

void calc_sz(int u, int p = -1) {
	sz[u] = 1;

	for(int v : e[u]) {
		if(v == p or morto[v]) continue;
		calc_sz(v, u);
		sz[u] += sz[v];
	}
}

int find_centroid(int u, int r, int p) {
	for(int v : e[u]) {
		if(v == p or morto[v]) continue;
		if(2 * sz[v] > sz[r]) return find_centroid(v, r, u);
	}
	return u;
}

void calc(int u, int p = -1, int l = 0) {
	bit.update(l, 1);
	for(int v : e[u]) {
		if(morto[v] or v == p) continue;
		calc(v, u, l + 1);
	}
}

void dfs(int u, int p = -1, int l = 0) {

	if(l >= L and l <= R) ans++;

	int LL = L - l;
	LL = max(LL, 0);
	int RR = R - l;
	if(LL <= RR) {
		ans += bit.query(LL, RR);
	}

	for(int v : e[u]) {
		if(morto[v] or v == p) continue;
		dfs(v, u, l + 1);
	}
}

void solve(int u) {
	calc_sz(u);
	int r = find_centroid(u, u, -1);

	morto[r] = 1;
	bit = Bit(sz[u]);
	for(int v : e[r]) {
		if(morto[v]) continue;
		dfs(v, -1, 1);
		calc(v, -1, 1);
	}

	// calcula pros outros centroides
	for(int v : e[r]) {
		if(morto[v]) continue;
		solve(v);
	}

	morto[r] = 0;

}

void _solve() {
	int l, r; cin >> n >> l >> r;

	for(int i = 1; i <= n; i++) e[i].clear();
	for(int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		e[u].pb(v);
		e[v].pb(u);
	}

	L = n - 1 - r; // distancia minima entre o par escolhido
	R = n - 1 - l; // distancia maxima entre o par escolhido

	ans = 0;
	solve(1);

	cout << ans << '\n';
}


int main() {
	freopen("awesome.in", "r", stdin);
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;

	while(t--) {
		_solve();
	}
}