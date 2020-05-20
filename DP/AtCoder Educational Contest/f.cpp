#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 3007;
string s, t;
int n, m;

int memo[N][N];

int solve(int i, int j) {
    if(i == n or j == m) return 0;
    int & st = memo[i][j];
    if(st == -1) {
        st = 0;
        if(s[i] == t[j]) st = 1 + solve(i+1, j+1);
        st = max(st, solve(i+1, j));
        st = max(st, solve(i, j+1));
    }
    return st;
}
string ans;
void build(int i, int j) {
    if(i == n or j == m) return;

    if(s[i] == t[j] and solve(i, j) == solve(i+1, j+1) + 1) {
        ans += s[i];
        build(i+1, j+1);
    } else if(solve(i, j) == solve(i+1, j)) {
        build(i+1, j);        
    } else {
        build(i, j+1);
    }
}
int main() {
    memset(memo, -1, sizeof memo);
    cin >> s >> t;
    n = s.size(), m = t.size();

    solve(0, 0);
    build(0, 0);
    cout << ans << endl;
}