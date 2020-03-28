// codeforces.com/contest/466/problem/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define eb emplace_back

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

void no() {
	cout << 0 << endl;
	exit(0);
}

const int N = 2007, M = 1000000007, inf = 0x3f3f3f3f;
int f[N][N];
int v[N];

int mul(ll a, ll b) {
	return a * b % M;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n, h;

	cin >> n >> h;

	for(int i = 1; i <= n; ++i) {
		cin >> v[i];
		if(v[i] > h) no();
		v[i] = h - v[i];
	}

	f[0][0] = 1;
	for(int i = 0; i <= n; ++i) {
		for(int o = 0; o <= i; ++o) {
			int x = v[i+1] - v[i];
			if(x == 1) {
				f[i+1][o+1] += f[i][o];
				f[i+1][o+1] %= M;
			} else if(x == -1) {
				f[i+1][o-1] += mul(f[i][o], o);
				f[i+1][o-1] %= M;
			} else if(x == 0) {
				f[i+1][o] += mul(f[i][o], o + 1);
				f[i+1][o] %= M;
			}
		}
	}

	cout << f[n+1][0] << endl;
	
}