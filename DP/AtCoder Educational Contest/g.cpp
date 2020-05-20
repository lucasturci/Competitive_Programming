#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1007, M = 1e9 + 7;

char mat[N][N];


int memo[N][N];
int n, m;

int solve(int i, int j) {
    if(i == n-1 and j == m-1) return 1;
    if(i >= n or j >= m) return 0;

    if(mat[i][j] == '#') return 0;
    
    int & st = memo[i][j];
    if(st == -1) {
        st = solve(i+1, j) + solve(i, j+1);
        st %= M;
    }
    return st;
}

int main() {
    memset(memo, -1, sizeof memo);
    cin >> n >> m;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> mat[i][j];
        }
    }

    cout << solve(0, 0) << endl;
}