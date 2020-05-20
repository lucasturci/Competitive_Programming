#include <bits/stdc++.h>

#define pb push_back
#define eb emplace_back
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 200007;

int a[N];

ll ans[N];
ii edges[N];
char two[N];
int sz[N], un[N];
vector<int> val[N], e[N];

vector<int> changed;

int find(int u) {
    if(un[u] == u) return u;
    return un[u] = find(un[u]);
}

// soma 
void unite(int u, int v, ll & x) {
    u = find(u), v = find(v);

    x += (ll) sz[u] * sz[v];
    if(sz[u] < sz[v]) swap(u, v);
    sz[u] += sz[v];
    un[v] = u;
    changed.pb(u);
    changed.pb(v);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        sz[i] = 1;
        un[i] = i;
        val[a[i]].pb(i);
    }

    for(int i = 0; i+1 < n; i++) {
        int u, v; cin >> u >> v;
        edges[i] = ii(u, v);
        e[u].pb(i);
        e[v].pb(i);
    }

    for(int x = 200000; x >= 1; --x) {
        vector<int> ed;
        for(int y = x; y <= 200000; y += x) {
            ans[x] -= ans[y];
            for(int u : val[y]) {
                ans[x] += 1;
                for(int j : e[u]) {
                    ed.pb(j);
                    two[j]++;
                    if(two[j] == 2) {
                        ii aux = edges[j];
                        unite(aux.fi, aux.se, ans[x]);
                    }
                }
            }
        }

        // cabou, reseta pro proximo. ans[x] ta calculado

        for(int j : ed) two[j] = 0;
        for(int u : changed) un[u] = u, sz[u] = 1;
        changed.clear();
    }

    for(int i = 1; i <= 200000; i++) {
        if(ans[i]) cout << i << ' ' << ans[i] << '\n';
    }


}