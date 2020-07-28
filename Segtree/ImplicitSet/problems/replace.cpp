/*
	https://codeforces.com/contest/911/problem/G

	The idea is to maintain segtrees to represent sets of positions for each value. For each operation, you split
	the set for the value of X to get the positions inside the interval and merge it with the set for the value of Y.
*/

#include <bits/stdc++.h>
using namespace std;
#define mid ((l+r) >> 1)

const int N = 12000007;

struct node {
	int l, r; // children left and right
	int s; // sum
};

int a[N];
int sets[N];

node seg[N];
stack<int> garbage; // If you are sure you wont use a node anymore, you can add it to garbage, to avoid MLE
int tt;

int new_node() {
	int u;
	if(garbage.size()) u = garbage.top(), garbage.pop();
	else u = ++tt;

	seg[u].l = seg[u].r = seg[u].s = 0;
	return u;
}

// add x occurences of j
void add(int & cur, int l, int r, int j, int x) {
	if(cur == 0) cur = new_node();
	if(l == r) {
		seg[cur].s += x;
	} else {
		if(j <= mid) add(seg[cur].l, l, mid, j, x);
		else add(seg[cur].r, mid+1, r, j, x);
		seg[cur].s = (seg[cur].l? seg[seg[cur].l].s : 0) + (seg[cur].r? seg[seg[cur].r].s : 0);
	}
}


inline int sz(int x) {
	return x == 0? 0 : seg[x].s;
}

// split t1 into t1 and t2, putting all less than or equal to x into t1
void split(int t1, int & t2, int l, int r, int x) {
	if(!t1) return;
	
	t2 = new_node();

	if(mid == x) {
		swap(seg[t1].r, seg[t2].r);
	} else if(mid < x) {
		split(seg[t1].r, seg[t2].r, mid+1, r, x);
	} else {
		swap(seg[t1].r, seg[t2].r);
		split(seg[t1].l, seg[t2].l, l, mid, x);
	}


	if(l == r) {
		if(x < mid) swap(seg[t1].s, seg[t2].s);
	} else {
		seg[t1].s = (seg[t1].l? seg[seg[t1].l].s : 0) + (seg[t1].r? seg[seg[t1].r].s : 0);
		seg[t2].s = (seg[t2].l? seg[seg[t2].l].s : 0) + (seg[t2].r? seg[seg[t2].r].s : 0);		
	}
}

// merging t1 and t2 into t1
void merge(int & t1, int t2) {
	if(!t1 or !t2) return void(t1 = (t1? t1 : t2));
	merge(seg[t1].l, seg[t2].l);
	merge(seg[t1].r, seg[t2].r);
	seg[t1].s += seg[t2].s;
	garbage.push(t2);
}

int query(int cur, int l, int r, int a, int b) {
	if(r < a or l > b or !cur) return 0;
	if(l >= a and r <= b) {
		return seg[cur].s;
	} else {
		return query(seg[cur].l, l, mid, a, b) + query(seg[cur].r, mid+1, r, a, b);
	}
}


void go(int cur, int l, int r, int val = 0) {
	if(!cur) return;
	if(l == r) {
		if(seg[cur].s) {
			a[l] = val;
		}
	} else {
		go(seg[cur].l, l, mid, val);
		go(seg[cur].r, mid+1, r, val);
	}
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, q; cin >> n >> q;

	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		add(sets[a[i]], 1, n, i, 1);
	}

	while(q--) {
		int op; cin >> op;

		int l, r, x, y;
		if(op == 1) {
			cin >> l >> r >> x >> y;
			int aux1 = 0, aux2 = 0;
			split(sets[x], aux1, 1, n, l-1);
			split(aux1, aux2, 1, n, r);

			merge(sets[x], aux2);
			merge(sets[y], aux1);
		} else {
			cin >> l >> r >> x;
			cout << query(sets[x], 1, n, l, r) << '\n';
		}

		
	}
}