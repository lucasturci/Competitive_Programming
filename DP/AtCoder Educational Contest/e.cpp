#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 107;
int w[N], v[N];
int n, W;

ll dp[2][100007];

ll infll;

int main() {
    memset(&infll, 0x3f, sizeof infll);
    cin >> n >> W;

    for(int i = 1; i <= n; ++i) {
        cin >> w[i] >> v[i];
    }

    int cur = 0;
    memset(dp, 0x3f, sizeof dp);
    dp[1-cur][0] = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j < 100007; ++j) {
            dp[cur][j] = dp[1-cur][j];
            if(j - v[i] >= 0 and dp[1-cur][j - v[i]] < infll) dp[cur][j] = min(dp[cur][j], w[i] + dp[1-cur][j - v[i]]);
        }
        cur = 1 - cur;
    }

    int ans = 0;
    for(int j = 0; j < 100007; ++j) {
        if(dp[1-cur][j] <= W) ans = max(ans, j);
    }

    cout << ans << endl;
}