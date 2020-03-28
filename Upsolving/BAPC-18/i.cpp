#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define eb emplace_back

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 100007, inf = 0x3f3f3f3f;

vector<int> e[N], w[N];
int p[N];
int much[N];

ll dist[12][N];

int n, m;

struct ed {
	int v;
	int cap, f;
    ll temp;
    int version;
	ed() {}
	ed(int a, ll b, ll c, ll x) {
		v = a;
		cap = b;
		f = c;
        temp = x;
        version = 0;
	}
};

// pro flow
ed arestas[2 * (N * 12 + N + 12)];
int cur = 0;
int d[N + 20], ptr[N + 20];
vector<int> edges[N + 20];

void add_edge(int u, int v, ll cap, ll temp) {
	arestas[cur] = ed(v, cap, 0, temp);
	edges[u].pb(cur);
	cur++;

	arestas[cur] = ed(u, cap, cap, temp);
	edges[v].pb(cur);
	cur++;
}
int version;
ll maxt;

int bfs(int s, int t) {
	int u, v;

	queue<int> q;
	memset(d, 0x3f, sizeof d);

	q.push(s);
	d[s] = 0;

	while(q.size()) {
		u = q.front();
		q.pop();
		for(int i = 0; i < edges[u].size(); ++i) {
			int p = edges[u][i];
			v = arestas[p].v;
			if(arestas[p].temp > maxt) break;
			if(arestas[p].version != version) {
				arestas[p].version = version;
				arestas[p].f = p%2 == 0? 0 : arestas[p].cap;
			}
			if(d[v] == inf and arestas[p].f < arestas[p].cap) {
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}

	return d[t] < inf;
}

int dfs(int u, int f, int t) {
	if(f == 0) return 0;
	if(u == t) return f;

	int v, p, tot;
	for(int& i = ptr[u]; i < edges[u].size(); ++i) {
		p = edges[u][i];
		v = arestas[p].v;

		if(arestas[p].temp > maxt) break;
		if(arestas[p].version != version) {
			arestas[p].version = version;
			arestas[p].f = p%2 == 0? 0 : arestas[p].cap;
		}
		if(d[v] == d[u] + 1) {
			tot = dfs(v, min(f, arestas[p].cap - arestas[p].f), t);
			if(tot) {
				arestas[p].f += tot;
				arestas[p^1].f -= tot;
				return tot;
			}
		}
	}
	return 0;
}

ll flow(int s, int t) {
	ll f = 0;

	while(bfs(s, t)) {
		memset(ptr, 0, sizeof ptr);
		while(ll tot = dfs(s, inf, t)) {
			f += tot;
		}
	}
	return f;
}


void dijkstra(int i, int s) {
	priority_queue<pair<ll, int> > pq;

	memset(dist[i], 0x3f, sizeof dist[i]);
	pq.push(make_pair(0, s));
	dist[i][s] = 0;

	int u; 
	ll d;
	while(pq.size()) {
		d = pq.top().fi;
		u = pq.top().se;
		pq.pop();
		d = -d;
		if(d > dist[i][u]) continue;

		for(int j = 0; j < e[u].size(); ++j) {
			int v = e[u][j];
			int c = w[u][j];

			if(dist[i][v] > dist[i][u] + c) {
				dist[i][v] = dist[i][u] + c;
				pq.push(make_pair(-dist[i][v], v));
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int S;
	cin >> n >> m >> S;

	ll people = 0;
	for(int i = 1; i <= n; ++i) {
		cin >> p[i];
		people += p[i];
	}

	for(int i = 0; i < m; ++i) {
		int u, v, c; cin >> u >> v >> c;

		e[u].pb(v);
		e[v].pb(u);
		w[u].pb(c);
		w[v].pb(c);
	}

	vector<int> shelters;

	for(int i = 0; i < S; ++i) {
		int a, c; cin >> a >> c;

		shelters.pb(a);

		much[i] = c;
	}

	for(int i = 0; i < S; ++i) {
		dijkstra(i, shelters[i]);
	}



	ll l = 0, r = 100000000000000ll;
	ll ans, mid, x;
	int s, t;
    // limpa o grafo do flow
    s = 0;
    t = n + S + 1;
    for(int i = 1; i <= n; ++i) {
        add_edge(s, i, p[i], 0);
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j < S; ++j) {

            add_edge(i, n + 1 + j, inf, dist[j][i]);
        }
    }
    for(int i = 0; i < S; ++i) {
        add_edge(n + 1 + i, t, much[i], 0);
    }

    for(int i = 0; i <= t; ++i) {
    	sort(edges[i].begin(), edges[i].end(), [=](int a, int b) {
    		return arestas[a].temp < arestas[b].temp;
    	});
    }

    while(l <= r) {
		mid = l + (r - l)/2;

		maxt = mid;
		// faz o grafo do flow, colocando aresta so onde o custo eh menor ou igual a mid
		// ve se o flow eh igual a todo mundo
		x = flow(s, t);
		
		if(x == people) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
		version++;
	}

	cout << ans << endl;
	

}