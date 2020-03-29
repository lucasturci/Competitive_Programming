/* https://maps20.kattis.com/problems/maps20.thewrathofkahn */
/*
 * Uses Dilworth's theorem (https://www.google.com.br/amp/s/www.geeksforgeeks.org/dilworths-theorem/amp/), that
 * says that the largest anti-chain of a partially ordered set is equal to the minimum number of chains that covers the set
 * 
 * Translating to graph world, chain is a path, partially ordered set is a DAG and the largest anti-chain is the width of the DAG
 * We only have to calculate minimum number of paths to cover a DAG, which is a classic problem and can be calculated with matching
 * 
 * This problem is equivalent to calculating the minimum number of *disjoint* paths to cover the transitive closure of the DAG,
 * which is a DAG where the existence of edge u->v and existence of edge v->w implies existence of edge u->w. Basically, there is
 * an edge u->v in the transitive closure of the DAG if there is a path from u to v in the original DAG.
 * 
 * To calculate this with matching, we can see the graph as if initially there are n paths of length 1 (each node alone). A matching
 * u -> v means, then, that we are merging the path that ends in u with the path that starts with v. So to calculate this we
 * duplicate the graph into a bipartite graph, and add edge u from the left side to v of the right side if u->v is present in the DAG.
 * Since everytime we add an edge we subtract the number of paths by one, because we want the maximum matching, we will achieve the minimum
 * number of paths. 
 * 
 * Another way to see this is as if each edge of the matching will become an edge of the path. But wait, each node can match up with two nodes, not one.
 * That's why we duplicate the nodes, into one (let's call it A) that only receives incoming edges, and another (let's call it B) which only has
 * outgoing edges coming out of it, and there is an implicit edge from A to B to construct the paths. That way, each node can only match with one other node,
 * and matching algorithm can work correctly.
 */
#include <bits/stdc++.h>

#define pb push_back

using namespace std;
typedef long long ll;

int n, m; 

const int N = 507;
vector<int> e[N], g[N];
int deg[N], in[N];

// simulate statements algorithm, to only recover the DAG we want
void algorithm() {
    queue<int> q;

    for(int u = 1; u <= n; ++u) {
        if(deg[u] == 0) q.push(u);
    }

    while(q.size()) {
        // remove node u
        int u = q.front(); q.pop();
        in[u] = 1;
        for(int v : e[u]) {
            deg[v]--;
            if(deg[v] == 0) q.push(v);
        }
    }
}

vector<int> filter(vector<int> vec, function<int (int)> cond) {
    vector<int> ans;
    for(int x : vec) if(cond(x)) ans.pb(x);
    return ans;
}

int vis[N];


void build(int u, int s) {
    vis[u] = 1;
    if(u != s) e[s].pb(u); 
    int sz = e[u].size();
    for(int i = 0; i < sz; ++i) {
        int v = e[u][i];
        if(vis[v] == 0) build(v, s);
    }
}

int match[N], umatch[N];

int dfs(int u) {
    if(vis[u]) return 0;
    vis[u] = 1;

    for(int v : g[u]) {
        if(match[v] == 0 or dfs(match[v])) {
            match[v] = u;
            umatch[u] = v;
            return 1;
        }
    }

    return 0;
}

int kuhn() {
    int ans = 0, flag = 1;

    while(flag) {
        memset(vis, 0, sizeof vis);
        flag = 0;
        for(int u = 1; u <= n; ++u) {
            if(in[u] and umatch[u] == 0 and dfs(u)) ans += (flag = 1);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;

    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        u++, v++;
        e[u].pb(v);
        deg[v]++;
    }

    algorithm();

    int cnt = 0;
    for(int i = 1; i <= n; ++i) {
        if(in[i]) {
            e[i] = filter(e[i], [](int x){return in[x];});
            cnt++;
        }
    }

    // Now you have the DAG you want

    // Transform in transitive closure
    for(int i = 1; i <= n; ++i) {
        if(in[i]) {
            memset(vis, 0, sizeof vis);
            build(i, i);
            sort(e[i].begin(), e[i].end());
            e[i].erase(unique(e[i].begin(), e[i].end()), e[i].end());
        }
    }

    // Now you do the matching
    for(int i = 1; i <= n; ++i) {
        if(in[i]) {
            g[i] = e[i];
        }   
    }

    int matching = kuhn();
    cout << cnt - matching << endl;
    
}