#include <bits/stdc++.h>

#define pb push_back
#define eb emplace_back
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> tiii;

vector<tiii> v;
int n; 

ll memo[1007][10007];



ll solve(int p, int w) {
	if(w >= 10007) return 0;
	if(p == n) {
		return 0;
	}

	ll & st = memo[p][w];

	if(st == -1) {
		int we, s, x;
		tie(we, s, x) = v[p];
		st = max(
			s >= w? x + solve(p+1, w + we) : (ll) -1e15,
			solve(p+1, w)
		);
	}
	return st;
}

int main() {
	memset(memo, -1, sizeof memo);
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n;

	for(int i = 0; i < n; i++) {
		int w, s, x; cin >> w >> s >> x;
		v.eb(w, s, x);
	}

	sort(v.rbegin(), v.rend(), [&](tiii aux1, tiii aux2) {
		int w1, s1, x1; tie(w1, s1, x1) = aux1;
		int w2, s2, x2; tie(w2, s2, x2) = aux2;

		return w1 + s1 > w2 + s2;
	});	

	cout << solve(0, 0) << '\n';
}
