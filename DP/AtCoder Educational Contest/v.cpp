#include <bits/stdc++.h>

#define pb push_back
#define eb emplace_back
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 200007, M = 1e9 + 7;

ll memo[N];
ii v[N];

ll fat[N];

ll fast_pow(ll a, ll b) {
	ll ans = 1;
	while(b) {
		if(b&1) ans = ans * a % M;
		b >>= 1;
		a = a * a % M;
	}
	return ans;
}

ll calc(ll L, ll R) {
	return fat[L + R] * fast_pow(fat[L] * fat[R] % M, M - 2) % M;
}

int n;

ll solve(int pos) {
	ll & st = memo[pos];
	if(st == -1) {
		int r, c; tie(r, c) = v[pos];
		st = calc(r-1, c-1);
		for(int i = 0; i < n; i++) {
			if(i == pos) continue;
			int p, q; tie(p, q) = v[i];
			if(p <= r and q <= c) {
				st = (st - (solve(i) * calc(r - p, c - q) % M) + M)%M;
			}
		}
	}
	return st;
}

int main() {
	memset(memo, -1, sizeof memo);
	ios::sync_with_stdio(0); cin.tie(0);

	fat[0] = 1;
	for(int i = 1; i < N; i++) {
		fat[i] = fat[i-1] * i % M;
	}

	int h, w; cin >> h >> w >> n;

	for(int i = 0; i < n; ++i) {
		int r, c; cin >> r >> c;
		v[i] = ii(r, c);
	}

	ll ans = calc(h-1, w-1);
	for(int i = 0; i < n; i++) {
		int p, q; tie(p, q) = v[i];
		ans = (ans - (solve(i) * calc(h - p, w - q) % M) + M)%M;

	}
	cout << ans << endl;
}
