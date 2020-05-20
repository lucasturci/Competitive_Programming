#include <bits/stdc++.h>

using namespace std;

int a[100007], b[100007], c[100007];
int memo[100007][4];
int n; 

int solve(int p, int last) {
    if(p == n) return 0;
    int & st = memo[p][last];
    if(st == -1) {
        st = max({
            last != 1? solve(p+1, 1) + a[p] : 0,
            last != 2? solve(p+1, 2) + b[p] : 0,
            last != 3? solve(p+1, 3) + c[p] : 0
        });
    }
    return st;
}
int main() {
    memset(memo, -1, sizeof memo);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }

    cout << solve(0, 0);
}