#include <bits/stdc++.h>

using namespace std;

int v[100007];
int main() {
int n, k; cin >> n >> k;
vector<int> dp(n+1);
for(int i=1; i <= n; ++i) cin >> v[i];
dp[n] = 0;
for(int i = n-1; i >= 1; --i) {
    dp[i] = 0x3f3f3f3f;
    for(int j = 1; j <= k and i + j <= n; ++j)
        dp[i] = min(dp[i], dp[i+j] + abs(v[i+j] - v[i]));
}

cout << dp[1] << endl;
}