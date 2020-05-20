#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define pb push_back

const int N = 100007;
const int M = 1e9 + 7;

vector<int> e[N];
int memo[N][2]; // vertice e cor do pai

int solve(int u, int c, int p = -1) {
    int & st = memo[u][c];
    if(st == -1) {
        st = 0;

        // pinta de black
        if(c == 0) {
            ll aux = 1;
            for(int v : e[u]) {
                if(v == p) continue;
                aux = aux * solve(v, 1, u) % M;
            }

            st = (st + aux)%M;
        }

        ll aux = 1;
        for(int v : e[u]) {
            if(v == p) continue;
            aux = aux * solve(v, 0, u) % M;
        }

        st = (st + aux)%M;        
    }
    return st;
}

int main() {
    memset(memo, -1, sizeof memo);
    int n; cin >> n;

    for(int i = 0; i < n-1; ++i) {
        int x, y; cin >> x >> y;
        e[x].pb(y);
        e[y].pb(x);
    }

    cout << solve(1, 0) << endl;
}
