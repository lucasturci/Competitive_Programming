#include <bits/stdc++.h>
 
#define pb push_back
#define mid ((l+r) >> 1)
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
const int N = 200007;
 
vector<ii> interv[N];
 
ll seg[4 * N];
ll lazy[4 * N];
 
const ll infll = 0x3f3f3f3f3f3f3f3fll;
 
void prop(int p, int l, int r) {
	if(lazy[p]) {
		seg[p] += lazy[p];
 
 
		if(l != r) {
			lazy[2 * p] += lazy[p];
			lazy[2 * p + 1] += lazy[p];
		}
	}
	lazy[p] = 0;
}
 
void update(int p, int l, int r, int a, int b, ll x) {
	prop(p, l, r);
	if(r < a or l > b) return;
	if(l >= a and r <= b) {
		lazy[p] += x;
		prop(p, l, r);
	} else {
		update(2 * p, l, mid, a, b, x);
		update(2 * p + 1, mid+1, r, a, b, x);
		seg[p] = max(seg[2 * p], seg[2 * p + 1]);
	}
}
 
ll query(int p, int l, int r, int a, int b) {
	prop(p, l, r);
	if(r < a or l > b) return -infll;
	if(l >= a and r <= b) {
		return seg[p];
	}
 
	return max(query(2 * p, l, mid, a, b), query(2 * p + 1, mid+1, r, a, b));
}
 
ll f[N];
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
 
	for(int i = 0; i < m; ++i) {
		int l, r, w; cin >> l >> r >> w;
 
		l--, r--;
		interv[l].eb(r, w);
	}
 
 
	for(int i = n-1; i >= 0; --i) {
		update(1, 0, n-1, i, i, f[i+1]);
 
		for(ii aux : interv[i]) {
			int r, w;
			tie(r, w) = aux;
 
			update(1, 0, n-1, i, r, w);
		}
 
		f[i] = max(0ll, query(1, 0, n-1, i, n-1));
	}
 
	cout << f[0] << '\n';
}
