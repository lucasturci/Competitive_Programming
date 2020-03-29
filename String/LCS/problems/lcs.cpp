// Uva problem 10405
#include <bits/stdc++.h>

using namespace std;

string s, t;

// iterative way
int lcs(string & s, string & t) {
    int n = s.size(), m = t.size();
    vector<vector<int> > mat(n, vector<int>(m));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            mat[i][j] = max({
                i? mat[i-1][j] : 0, 
                j? mat[i][j-1] : 0, 
                (i and j? mat[i-1][j-1] : 0) + (s[i] == t[j])
            });
        }
    }
    return mat[n-1][m-1];
}


// recursive way
int memo[1007][1007];
int lcs2(int i, int j) {
    if(i == s.size() or j == t.size()) return 0;
    int & st = memo[i][j];
    if(st == -1) {
        if(s[i] == t[j]) st = max(st, lcs2(i+1, j+1) + 1);
        st = max(st, lcs2(i+1, j));
        st = max(st, lcs2(i, j+1));
    }
    return st;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    while(getline(cin, s) and getline(cin, t)) {
        memset(memo, -1, sizeof memo);
        int ans1 = lcs(s, t), ans2 = lcs2(0, 0);
        assert(ans1 == ans2);
        cout << ans1 << '\n';
    }
}