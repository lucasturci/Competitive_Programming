#include <bits/stdc++.h>

// WARNING: L E R ONE BASED NAS QUERIES (NA ESTRUTURA O ACESSO EH ZERO BASED, MAS ISSO EH CORRIGIDO PELO CODIGO)

using namespace std;
typedef long long ll;

#define pb push_back

#define left(p, i) (i? mapLeft[p][i-1] : 0)
#define right(p, i) (i - left(p, i))
#define toLeft(p, i) (left(p, i) - left(p, i-1))
#define toRight(p, i) (right(p, i) - right(p, i-1))

const int A = 100007, N = 100007; // A = tam alfabeto, N = tam vetor

vector<int> mapLeft[4 * A];
int v[N];

// valores estao entre a e b
void build(int p, int a, int b, vector<int> & vec) {
	if(a != b) {
		int mid = (a + b)/2;

		mapLeft[p].resize(vec.size());
		vector<int> L, R;
		for(int i = 0; i < vec.size(); ++i) {
			if(vec[i] <= mid) {
				mapLeft[p][i] = left(p, i) + 1;
				L.pb(vec[i]);
			} else {
				mapLeft[p][i] = left(p, i);
				R.pb(vec[i]);
			}
		}
		build(2 * p, a, mid, L);
		build(2 * p + 1, mid+1, b, R);
	}
}

// quantos valores entre x e y no intervalo [l, r] (one-based)
int count(int p, int a, int b, int l, int r, int x, int y) {
	if(y < a or b < x) return 0;
	if(x <= a and b <= y) {
		return r - l + 1;
	} else {
		int mid = (a + b)/2;
		return 	count(2 * p, a, mid, left(p, l-1) + 1, left(p, r), x, y) + 
				count(2 * p + 1, mid+1, b, right(p, l-1) + 1, right(p, r), x, y);
	}
}

// k-esimo menor valor no intervalo [l, r]
int quantile(int p, int a, int b, int l, int r, int k) {
	if(a == b) return a;

	int mid = (a + b)/2;
	int L = left(p, l-1) + 1, R = left(p, r);

	if(R - L + 1 >= k) return quantile(2 * p, a, mid, L, R, k);
	else return quantile(2 * p + 1, mid+1, b, right(p, l-1) + 1, right(p, r), k - (R - L + 1));
}

// swap j com j + 1 (one based tbm)
void swap(int p, int a, int b, int j) {
	assert(j >= 1 and j + 1 <= mapLeft[p].size());
	if(a == b) return;

	int mid = (a + b)/2;

	if(toLeft(p, j) and toLeft(p, j+1)) swap(2 * p, a, mid, left(p, j-1) + 1);
	else if(toRight(p, j) and toRight(p, j+1)) swap(2 * p + 1, mid+1, b, right(p, j-1) + 1);
	else { // so vai afetar esses dois, dali pra frente nao vai afetar mais nada
		if(toLeft(p, j)) mapLeft[p][j-1]--;
		else mapLeft[p][j-1]++;
	}
}

void wavelet_push_back(int p, int a, int b, int x) {
	if(a == b) return;
	int mid = (a + b)/2;

	mapLeft[p].pb((x <= mid) + left(p, mapLeft[p].size()));
	if(x <= mid) wavelet_push_back(2 * p, a, mid, x);
	else wavelet_push_back(2 * p + 1, mid+1, b, x);
}

void wavelet_pop_back(int p, int a, int b) {
	if(a == b) return;
	int mid = (a + b)/2;
	
	int l = toLeft(p, mapLeft[p].size());
	mapLeft[p].pop_back();
	if(l) wavelet_pop_back(2 * p, a, mid);
	else wavelet_pop_back(2 * p + 1, mid+1, b);
}



int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n; cin >> n;

	for(int i = 1; i <= n; ++i) {
		cin >> v[i];
	}

	vector<int> aux(v + 1, v + n + 1);
	build(1, 1, A, aux);

}