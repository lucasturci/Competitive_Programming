#include <bits/stdc++.h>

using namespace std;

int v[100007];
int main() {
int n; cin >> n;
vector<int> dp(n+1);
for(int i=1; i <= n; ++i) cin >> v[i];
dp[n] = 0;
dp[n-1] = abs(v[n] - v[n-1]);
for(int i = n-2; i >= 1; --i) {
dp[i] = min(dp[i+1] + abs(v[i+1] - v[i]), dp[i + 2] + abs(v[i+2] - v[i]));
}

cout << dp[1] << endl;
}