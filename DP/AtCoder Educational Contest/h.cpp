#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 3007;

double prob[N];

double memo[N][2 * N];
bool vis[N][2 * N];

double solve(int p, int s) {
    if(p < 0) {
        if(s > 0) return 1;
        else return 0;
    }

    double & st = memo[p][s + 3000];
    if(vis[p][s + 3000] == false) {
        vis[p][s + 3000] = true;
        st = prob[p] * solve(p-1, s+1) + (1 - prob[p]) * solve(p-1, s-1);
    }
    return st;
}

int main() {
    int n; cin >> n;

    for(int i = 0; i < n; ++i) {
        cin >> prob[i];
    }

    cout << fixed << setprecision(10) <<  solve(n-1, 0) << endl;
}
