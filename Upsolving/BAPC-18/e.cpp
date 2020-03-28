#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;


const int M = 1000000009, N = 5007;
int v[N];

int fast_pow(ll a, ll b) {
	ll ans = 1;
	while(b) {
		if(b&1) ans = (ans * a)%M;
		b >>= 1;
		a = (a * a)%M;
	}
	return ans;
}

int divide(ll a, ll b) {
	return a * fast_pow(b, M - 2) % M;
}

ll ans[N];
ll pre[N][N];
ll inv[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n; cin >> n;

	for(int i = 1; i < N; ++i) {
		inv[i] = fast_pow(i, M - 2);
	}

	for(int i = 0; i < n; ++i) {
		cin >> v[i];
	}

	sort(v, v + n);
	v[n] = -1; // pra ser diferentao

	// comprime
	int a, cur = 0;
	for(int i = 0; i < n; ++i) {
		a = v[i];
		v[i] = cur;
		if(a != v[i+1]) cur++;
	}

	// pre[i][j] = numero de permutacoes sem repeticao de i ate j
	for(int i = 0; i < n; ++i) {
		ll cur = 1;
		int step = 1;
		for(int j = i; j < n; ++j) {
			if(j == i or v[j] != v[j-1]) {
				step = 1;
			} else {
				step++;
			}
			cur = cur * (j - i + 1) % M;
			cur = cur * inv[step] % M;
			pre[i][j] = cur;
		}
	}

	ll per;
	int j;
	// vou calcular prefixo por prefixo, pra poder usar mais pra frente
	for(int i = 0; i < n; ++i) {
		// calcula o numero de permutacoes total do array
		ans[i] = pre[0][i];

		// remove pra cada j, o numero de permutacoes em que j é o primeiro sorted
		for(j = 0; j <= i; ++j) {
			per = j == i? 1 : pre[j+1][i];
			per = per * (j? ans[j-1] : 1ll) % M;
			ans[i] = (ans[i] - per + M) % M;
		}
	}

	cout << ans[n-1] << endl;
}