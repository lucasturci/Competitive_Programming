#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

const int MAX = 1000007, inf = 0x3f3f3f3f;

ll X0, Y0, X1, Y1;
ll v[MAX], r[MAX];
int n;

//resposta = (X0, Y0)
void gcd_ext(ll a, ll b) {
	ll X, Y;

	if(b == 0) return; 

	X = X0 - (a/b) * X1;
	Y = Y0 - (a/b) * Y1;

	X0 = X1, Y0 = Y1;
	X1 = X, Y1 = Y;

	gcd_ext(b, a%b);
}

ll solve() {
	ll x = 0, N = 1;

	for(int i = 0; i < n; ++i) N *= v[i];
	for(int i = 0; i < n; ++i) {
		ll y = N/v[i];

		X0 = 1, Y0 = 0;
		X1 = 0, Y1 = 1;
		gcd_ext(y, v[i]);

		ll z = X0 % N;
		x = (x + ((y * z) % N * r[i]) % N) % N;
	}
	return x;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;

	for(int i = 0; i < n; ++i) cin >> v[i];
	for(int i = 0; i < n; ++i) cin >> r[i];

	cout << solve() << endl;

	
}