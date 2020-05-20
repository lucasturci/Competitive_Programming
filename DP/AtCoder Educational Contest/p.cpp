#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define pb push_back

typedef vector<ll> vll;
typedef vector<vll> vvll;

const int N = 57;
const int M = 1e9 + 7;
ll n, k;

vvll ident(int n) {
    vvll ans(n, vll(n, 0));
    for(int i = 0; i < n; ++i) ans[i][i] = 1;
    return ans;
}

vvll mult(vvll a, vvll b) {
    vvll ans(a.size(), vll(b[0].size()));

    for(int i = 0; i < a.size(); ++i) {
        for(int j = 0; j < b[0].size(); j++) {
            ans[i][j] = 0;
            for(int l = 0; l < a.size(); l++) {
                ans[i][j] = (ans[i][j] + a[i][l] * b[l][j])%M;
            }
        }
    }
    return ans;
}

vvll fast_exp(vvll mat, ll k) {
    vvll ans = ident(n);
    while(k) {
        if(k&1) ans = mult(ans, mat);
        k >>= 1;
        mat = mult(mat, mat);
    }
    return ans;
}

int main() {
    cin >> n >> k;
    vvll mat(n, vll(n));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> mat[i][j];
        }
    }

    vvll ans = fast_exp(mat, k);
    
    ll tot = 0;
    for(vll & aux : ans) for(ll & x : aux) tot = (tot + x)%M;
    cout << tot << endl;
}
