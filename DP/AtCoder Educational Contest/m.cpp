#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 21;
const int M = 1e9 + 7;

int mat[N][N];
int memo[N + 7][(1 << N) + 7];
int n; 

int solve(int i, int mask) {
    if(i == n) return 1;
    int & st = memo[i][mask];

    if(st == -1) {
        st = 0;
        for(int j = 0; j < n; j++) {
            if((mask >> j)&1) continue;
            if(mat[i][j] == 0) continue;
            st = (st + solve(i+1, mask | (1 << j)))%M;
        }
    }
    return st;
}

int main() {
    memset(memo, -1, sizeof memo);
    cin >> n;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> mat[i][j];
        }
    }

    cout << solve(0, 0) << endl;
}
