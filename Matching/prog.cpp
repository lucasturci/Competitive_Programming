#include <bits/stdc++.h>
#define pb push_back

using namespace std;
const int N = 100007;

int n, m, e, match[N], vis[N], umatch[N];
vector<int> edges[N+N];

int dfs(int u) {
	if(vis[u]) return 0;
	vis[u] = 1;

	for(int v : edges[u]) {
		if(match[v] == 0 or (match[v] and dfs(match[v]))) {
			umatch[u] = v;
			match[v] = u;
			return 1;
		}
	}
	return 0;
}

int solve() {
	int flag, tot = 0;

	do {
		flag = 0;
		memset(vis, 0, sizeof vis);
		for(int u = 1; u <= n; ++u) {
			if(umatch[u] == 0 and dfs(u)) tot += (flag = 1);
		}

	} while(flag);
	return tot;
}

int main() {
	
	scanf("%d %d %d", &n, &m, &e);

	for(int i = 0; i < e; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		edges[u].pb(v+n);
	}

	printf("%d\n", solve());
}