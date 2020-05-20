#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll f[2][100007];

int w[107], v[107];

int main() {
    int n, W;
    cin >> n >> W;

    for(int i = 0; i < n; ++i) {
        cin >> w[i] >> v[i];
    }

    int cur = 0;

    memset(f, -1, sizeof f);
    f[1-cur][0] = 0;
    for(int i = 0; i < n; ++i) {
        memcpy(f[cur], f[1-cur], sizeof f[cur]);
        for(int j = 0; j <= W; ++j) {
            if(j - w[i] >= 0 and f[1-cur][j - w[i]] >= 0) f[cur][j] = max(f[cur][j], f[1 - cur][j - w[i]] + v[i]);
        }
        cur = 1 - cur;
    }

    ll ans = 0;
    for(int j = 0; j <= W; ++j) {
        ans = max(ans, f[1 - cur][j]);
    }
    cout << ans << endl;
}