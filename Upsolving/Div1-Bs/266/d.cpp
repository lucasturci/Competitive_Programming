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

int memo[N][N];
int v[N];
int n;

int mul(ll a, ll b) {
	return a * b % M;
}

int solve(int p, int op) {
	if(p == n + 2) {
		return 1;
	}
	int & st = memo[p][op];

	if(st == -1) {
		int diff = v[p] - v[p-1];

		if(diff == 0) { // tira um e faz um novo ou nao faz nada
			st = mul(op + 1, solve(p+1, op));
		} else if(diff == -1) { // tira um
			if(op == 0) st = 0;
			else st = mul(op, solve(p+1, op-1));
		} else if(diff == 1) { // cria um
			st = solve(p+1, op+1);
		} else st = 0;
	}
	return st;
}

int main() {
	memset(memo, -1, sizeof memo);
	ios::sync_with_stdio(0); cin.tie(0);
	int h;

	cin >> n >> h;

	for(int i = 1; i <= n; ++i) {
		cin >> v[i];
		if(v[i] > h) no();
		v[i] = h - v[i];
	}

	cout << solve(1, 0) << endl;
}