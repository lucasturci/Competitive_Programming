// https://codeforces.com/gym/102501/problem/K
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

using namespace std;
typedef pair<int, int> ii;

const int N = 200007;
vector<int> e[N], rev[N];
vector<int> sd[N]; // semidominated, sd[u] = {v | sdom[v] = u}

int tim[N], inv_tim[N], par[N];
int sdom[N], idom[N];
int un[N], path[N];
int cnt[N];


// Finds the guy that has least sdom in the ancestors of u, and uses path compression to optimize it
ii query(int u) {
    if(u == un[u]) return ii(u, u);
    int p;
    tie(p, un[u]) = query(un[u]);
    if(sdom[p] < sdom[path[u]]) path[u] = p;
    return ii(path[u], un[u]);
}

int tt;
void dfs(int u) {
    tim[u] = ++tt;
    inv_tim[tt] = u;
    for(int v : e[u]) {
        if(!tim[v]) {
            dfs(v);
            par[tim[v]] = tim[u];
        }
    }
}
void build() {
    for(int u = 1; u <= tt; ++u) sdom[u] = idom[u] = un[u] = path[u] = u;
    for(int u = tt; u >= 1; --u) {
        for(int v : rev[inv_tim[u]]) {
            v = tim[v];
            if(v == 0) continue;
            if(v < u) sdom[u] = min(sdom[u], sdom[v]);
            else sdom[u] = min(sdom[u], sdom[query(v).fi]);
        }
        sd[sdom[u]].pb(u);

        for(int v : sd[u]) {
            int best = query(v).fi;
            if(sdom[best] >= u) idom[v] = u;
            else idom[v] = best;
        }

        for(int v : e[inv_tim[u]]) {
            v = tim[v];
            if(v == 0) continue;

            if(par[v] == u) un[v] = u; // if u->v is tree edge, add it
        }
    }
    for(int u = 1; u <= tt; ++u) 
        if(idom[u] != sdom[u]) idom[u] = idom[idom[u]];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m, t; cin >> n >> m >> t; 

    vector<int> cand;
    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;

        if(v == t) {
            e[v].pb(n + u);
            rev[n + u].pb(v);
            e[n + u].pb(u);
            rev[u].pb(n + u);
            cand.pb(u);
        } else {
            e[v].pb(u);
            rev[u].pb(v);
        }
        
    }

    dfs(t);
    build();

    vector<int> ans;
    for(int u : cand) {
        if(idom[tim[u]] == tim[n + u]) {
            ans.pb(u);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for(int u : ans) cout << u << '\n';
}