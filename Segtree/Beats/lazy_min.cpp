#include <bits/stdc++.h>
/*
	Segtree range query - range update, em que o update é do tipo: seg_i := min(seg_i, x) pra todo l <= i <= r
	Da pra fazer com maximo tambem, e da pra juntar maximo e minimo
	Complexidade permanece O(log N) amortizado por query

	Ideia: potencial de um intervalo é o numero de caras diferentes no intervalo. Só vou descer no intervalo
	se o potencial diminuir, tal que se o potencial for 1, nao vou descer mais. Por isso só desce se x
	for menor que o segundo maior do intervalo, porque ai o segundo maior e o maior ficam iguais e o potencial
	reduz em 1.

	NOT TESTED
*/

#define mid ((l+r)>>1)
using namespace std;
typedef long long ll;
const int N = 200007, inf = 0x3f3f3f3f;

ll seg[4 * N]; // o que a seg realmente guarda (no caso, soma)
int mai[4 * N]; // maior do intervalo
int seg_mai[4 * N]; // segundo maior do intervalo
int cnt_mai[4 * N]; // conta quantos elementos nesse intervalo sao iguais ao maior
int lazy[4 * N];

void merge(int p, int l, int r) {
	if(mai[l] == mai[r]) {
		mai[p] = mai[l];
		cnt_mai[p] = cnt_mai[l] + cnt_mai[r];
		seg_mai[p] = max(seg_mai[l], seg_mai[r]);
	} else {
		if(mai[l] < mai[r]) swap(l, r);
		mai[p] = mai[l];
		cnt_mai[p] = cnt_mai[l];
		seg_mai[p] = max(seg_mai[l], mai[r]);
	}

	seg[p] = seg[l] + seg[r];
}

void build(int p, int l, int r) {	
	if(l == r) {
		mai[p] = seg[p] = inf;
		seg_mai[p] = -inf; // menor valor que posso ter
		cnt_mai[p] = 1;
	} else {
		build(2 * p, l, mid);
		build(2 * p + 1, mid+1, r);
		merge(p, 2 * p, 2 * p + 1);
	}
	lazy[p] = inf;
}

void prop(int p, int l, int r) {
	if(lazy[p] < mai[p]) {
		seg[p] -= ll(mai[p] - lazy[p]) * cnt_mai[p];
		mai[p] = lazy[p];
	}

	if(l != r) {
		lazy[2 * p] = min(lazy[2 * p], lazy[p]);
		lazy[2 * p + 1] = min(lazy[2 * p + 1], lazy[p]);
	}

	lazy[p] = inf;
}

// para todo i em [a, b], atualiza seg_i = min(seg_i, x)
void update(int p, int l, int r, int a, int b, int x) {
	prop(p, l, r);
	if(r < a or l > b or mai[p] <= x) return;
	if(l >= a and r <= b and seg_mai[p] < x) {
		lazy[p] = min(lazy[p], x);
		prop(p, l, r);
	} else {
		update(2 * p, l, mid, a, b, x);
		update(2 * p + 1, mid+1, r, a, b, x);
		merge(p, 2 * p, 2 * p + 1);
	}
}

// retorna a soma de [a, b]
ll query(int p, int l, int r, int a, int b) {
	prop(p, l, r);
	if(r < a or l > b) return 0;
	if(l >= a and r <= b) return seg[p];
	return query(2 * p, l, mid, a, b) + query(2 * p + 1, mid+1, r, a, b);
}

void debug(int n) {
	cout << "Printando segtree\n";
	for(int i = 1; i <= n; ++i) {
		cout << query(1, 1, n, i, i) << ' ';
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, q; cin >> n;

	build(1, 1, n);

	int op, l, r, x; 
	while(cin >> op >> l >> r) {
		if(op == 1) {
			cout << query(1, 1, n, l, r) << '\n';
		} else {
			cin >> x;
			update(1, 1, n, l, r, x);
		}
		// debug(n);
	}
}