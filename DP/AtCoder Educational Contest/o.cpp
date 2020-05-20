#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define pb push_back

const int N = 200007;

ll f[N];
int h[N], a[N];

ll seg[N + N];

void update(int p, ll val) {
    p += N;
    for(seg[p] = max(seg[p], val); p > 1; p >>= 1) {
        seg[p >> 1] = max(seg[p], seg[p^1]);
    }
}

ll query(int l, int r) {
    ll ans = 0;
    for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if(l&1) ans = max(ans, seg[l++]);
        if(r&1) ans = max(ans, seg[--r]);
    }
    return ans;
}

int main() {
    int n; cin >> n;

    for(int i = 0; i < n; ++i) cin >> h[i];
    for(int i = 0; i < n; ++i) cin >> a[i];

    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        ll x = query(1, h[i]);
        f[i] = x + a[i];
        update(h[i], f[i]);
        ans = max(ans, f[i]);
    }

    cout << ans << endl;


}
