#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define eb emplace_back

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 100007;
vector<int> e[N];
int deg[N];

int main() {
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m, k; cin >> n >> m >> k;

    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        e[u].pb(v);
        deg[v]++;
    }

    int last = 0;

    vector<ii> ans;
    set<int> active, blocked;
    for(int i = 1; i <= n; ++i) {
        if(deg[i] == 0) active.insert(i);
    }

    while(active.size() or blocked.size()) {
        
        int mai = max(active.size()? *active.rbegin() : 0, blocked.size()? *blocked.rbegin() : 0);
        assert(mai > 0);

        if(active.size()) {
            int u = *active.begin();
            if(u < mai and k) {
                active.erase(active.begin());
                blocked.insert(u);
                k--;
            } else {
                last = u;
                cout << u << ' ';
                active.erase(u);
                for(int v : e[u]) {
                    deg[v]--;
                    if(deg[v] == 0) active.insert(v);
                }
            }
        } else {
            ans.emplace_back(last, mai);
            last = mai;
            cout << mai << ' ';

            blocked.erase(mai);
            for(int v : e[mai]) {
                deg[v]--;
                if(deg[v] == 0) active.insert(v);
            }
        }
    }
    cout << endl;
    cout << ans.size() << endl;
    for(ii aux : ans) cout << aux.fi << ' ' << aux.se << endl;

}