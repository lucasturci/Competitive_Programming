#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 300007;
ll acc[N];
int mai[N];
int par[N], imp[N];
ll v[N];

inline int cnt(ll a) {
	int tot = 0;
	while(a) {
		tot += (a&1);
		a >>= 1;
	}
	return tot;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;

	for(int i = 0; i < n; ++i) {
		cin >> v[i];
		v[i] = cnt(v[i]);
	}

	mai[0] = -1;
	for(int i = 1; i < n; ++i) {
		int & j = mai[i];
		for(j = i-1; j >= 0 and v[j] <= v[i]; j = mai[j]);
	}

	acc[0] = v[0];
	par[0] = 1;
	imp[0] = 0;
	for(int i = 1; i < n; ++i) {
		acc[i] = v[i] + acc[i-1];
		par[i] = par[i-1] + (acc[i-1]%2 == 0);
		imp[i] = imp[i-1] + (acc[i-1]%2);
	}

	ll tot = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = i; j >= 0; j = mai[j]) {
			int l = mai[j]+1;
			// v[j] <= soma - v[j]
			// v[j] <= acc[i] - acc[p] - v[j]
			// acc[p] <= acc[i] - 2 * v[j]
			int r = -1;

			int lo = l, hi = j;
			while(lo <= hi) {
				int mid = (lo + hi)/2;
				if(v[j] <= acc[i] - (mid == 0? 0 : acc[mid-1]) - v[j]) {
					r = mid;
					lo = mid+1;
				} else {
					hi = mid-1;
				}
			}

			if(r == -1) continue;

			if(acc[i]%2) {
				tot += imp[r] - (l == 0? 0 : imp[l-1]);
			} else {
				tot += par[r] - (l == 0? 0 : par[l-1]);
			}
		}
	}

	cout << tot << endl;
}