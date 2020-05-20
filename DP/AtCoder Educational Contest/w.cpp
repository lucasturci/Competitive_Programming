#include <bits/stdc++.h>

#define pb push_back
#define eb emplace_back
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 200007;

const ll isQuery = -(1LL << 62);

struct Line {
	ll m, b;int id;
	Line(ll m_, ll b_, int id_) : m(m_), b(b_), id(id_) {}
	mutable multiset<Line>::iterator it, e;
	const Line * succ() const {
		return next(it)==e ? 0 : &*next(it);
	}
	bool operator<(const Line& rhs) const {
		if(rhs.b != isQuery) return m < rhs.m;
		const Line* s = succ();
		if (!s) return 0;
		ll x=rhs.m;
		return b - s->b < (s->m - m) * x;
	}
};

struct DynamicHull : public multiset<Line> {
	bool bad(iterator y) {
		auto z=next(y);
		if(y == begin()) {
			if (z == end()) return 0;
			return y->m == z -> m && y->b <= z->b;
		}
		auto x = prev(y);
		if(z == end()) return y->m == x->m and y->b <= x->b;
		return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
	}

	void insertLine(ll m, ll b, int id) {
		auto y = insert({m, b, id});
		y->it = y;
		y->e = end();
		if(bad(y)) { erase(y); return; }
		while( next(y) != end() and bad(next(y)) ) erase(next(y));
		while(y != begin() and bad(prev(y))) erase(prev(y));
	}

	pair<ll, int> getMax(ll x) {
		auto l = *lower_bound({x, isQuery, 0});
		return {l.m * x + l.b, l.id};
	}
};

ll h[N];
ll f[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	ll c;

	cin >> n >> c;

	DynamicHull hull;
	for(int i = 0; i < n; i++) {
		cin >> h[i];
	}

	for(int i = n-1; i >= 0; --i) {
		if(i < n-1) f[i] = h[i] * h[i] + c;
		else f[i] = 0;


		if(hull.size()) f[i] -= hull.getMax(h[i]).fi;

		hull.insertLine(2ll * h[i], -(h[i] * h[i] + f[i]), i);
	}

	cout << f[0] << '\n';
}
