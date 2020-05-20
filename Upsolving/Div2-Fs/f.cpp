#include <bits/stdc++.h>

#define fi first
#define se second
#define pb push_back

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 1000017;

vector<int> e[N];

int dep[N];
int pai[N][21], vis[N][2];

int tt;
void dfs(int u, int p = 1, int d = 0) {
    dep[u] = d;

    pai[u][0] = p;
    vis[u][0] = ++tt;
    for(int i = 1; i < 21; ++i)
        pai[u][i] = pai[pai[u][i-1]][i-1];

    for(int v : e[u]) {
        if(v == p) continue;
        dfs(v, u, d + 1);
    }
    vis[u][1] = tt;
}

int lca(int u, int v) {
    if(u == v) return u;
    if(vis[u][0] > vis[v][0]) swap(u, v);

    for(int i = 20; i >= 0; --i) {
        int w = pai[v][i];
        if(vis[w][0] > vis[u][0]) v = w;
    }
    return pai[v][0];
}

inline int dist(int u, int v) {
    int uv = lca(u, v);
    return dep[u] + dep[v] - 2 * dep[uv];
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int q; cin >> q;

    // simula primeiro

    int n = 4;
    e[1] = {2, 3, 4};
    e[2].pb(1);
    e[3].pb(1);
    e[4].pb(1);

    for(int i = 0; i < q; ++i) {
        int u;
        cin >> u;
        e[u].pb(++n);
        e[n].pb(u);
        e[u].pb(++n);
        e[n].pb(u);

    }

    dfs(1);

    int end1, end2;
    end1 = 2, end2 = 3;

    int diam = 2;

    for(int i = 5; i <= n; ++i) {
        int d1 = dist(i, end1);
        int d2 = dist(i, end2);
        if(d1 > diam) {
            diam = d1;
            end2 = i;
        }
        if(d2 > diam) {
            diam = d2;
            end1 = i;
        }
        if(i%2 == 0) cout << diam << '\n';
    }

    
}