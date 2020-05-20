#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 3007;

int a[N];
int n; 
ll memo[N][N];
ll solve(int l, int r) {
    if(l > r) return 0;
    ll & st = memo[l][r];
    if(st == -1) {
        int turn = (l - 0 + (n - 1 - r))%2;

        if(turn == 0) {
            st = max(solve(l+1, r) + a[l], solve(l, r-1) + a[r]);
        } else {
            st = min(solve(l+1, r) - a[l], solve(l, r-1) - a[r]);
        }
    }
    return st;
}

int main() {
    memset(memo, -1, sizeof memo);
    cin >> n;

    for(int i = 0; i < n; ++i) cin >> a[i];    

    cout << solve(0, n-1) << endl;
}
