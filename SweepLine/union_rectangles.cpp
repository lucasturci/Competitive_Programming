#include <bits/stdc++.h>
 
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define debug 0
 
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
 
const int N = 100007;
 
int range[N];
vector<ii> vec; // vector do sweep line
ii side[N]; // guarda o y de baixo e o y de cima do retangulo i
 
int all[4 * N], seg[4 * N];

set<int> ids[4 * N];
 
void build(int p, int l, int r) {
    if(l == r) {
        all[p] = range[l];
    } else {
        int m = (l + r)/2;
        build(2 * p, l, m);
        build(2 * p + 1, m+1, r);
        all[p] = all[2 * p] + all[2 * p + 1];
    }
}
 
int update(int p, int l, int r, int a, int b, int x) {
    if(l > b or r < a) return 0;
    if(l >= a and r <= b) {
        if(x > 0) {
            ids[p].insert(x);
        } else {
            ids[p].erase(-x);
        }
    } else {
        int m = (l + r)/2;
        update(2 * p, l, m, a, b, x);
        update(2 * p + 1, m+1, r, a, b, x);
        seg[p] = ids[2 * p].size() ? all[2 * p] : seg[2 * p];
        seg[p] += ids[2 * p + 1].size() ? all[2 * p + 1] : seg[2 * p + 1];
    }

    if(p == 1) return seg[p];
    return 0;
}

void print_segtree() {
	printf("Printando a segtree\n");

	for(int i = 1; i <= 9; ++i) {
		printf("seg[%d] = %d, com valores [", i, seg[i]);
		for(int x : ids[i]) printf("%d%s", x, x == *ids[i].rbegin()? "" : ", ");
		printf("]\n");
	}
}
 
int main() {
    int n; 
    scanf("%d", &n);
 
    vector<int> Y;
    for(int i = 1; i <= n; ++i) {
        int x1, y1, x2, y2;
        scanf("%d %d", &x1, &y1);
        scanf("%d %d", &x2, &y2);
 
        side[i] = ii(y1, y2);
        vec.eb(x1, i);
        vec.eb(x2, -i);
 
        Y.pb(y1); Y.pb(y2);
    }
    
    string s;
 
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
 
 
    for(int i = 0; i < ((int)Y.size())-1; ++i)
        range[i] = Y[i+1] - Y[i];

    if(debug) for(int x : Y) cout << x << " ";
    if(debug) cout << endl;

    if(debug) for(int i = 0; i < (int) Y.size()-1; ++i) cout << range[i] << " ";
    if(debug) cout << endl;
 
    sort(vec.begin(), vec.end());
    
 
    build(1, 0, Y.size()-1);
 
 
    int length = 0;
 
    int cnt = 0; // conta quantos retangulos ativos tem
    int last; // ultimo x analisado
    ll ans = 0;
    for(int i = 0; i < vec.size(); ++i) {
        ii aux = vec[i];
        int x = aux.first, id = aux.second;
 
 		if(debug) printf("A aresta id = %d de posicao x = %d tem last = %d e o comprimento atual eh %d\n", abs(id), x, last, length);
        if(id > 0) { // entrada
            if(cnt)
                ans += ll(x - last) * length;
 
            int y1, y2;
            y1 = side[id].first, y2 = side[id].second;

            y1 = lower_bound(Y.begin(), Y.end(), y1) - Y.begin();
            y2 = lower_bound(Y.begin(), Y.end(), y2) - Y.begin();
 
 			if(debug) printf("Adicionando o intervalo de [%d, %d] com id = %d\n", y1, y2 - 1, id);
            length = update(1, 0, Y.size()-1, y1, y2-1, id);
 
            cnt++;
        } else {
            ans += ll(x - last) * length;
 
            int y1, y2;
            y1 = side[-id].first, y2 = side[-id].second;
 
 
            y1 = lower_bound(Y.begin(), Y.end(), y1) - Y.begin();
            y2 = lower_bound(Y.begin(), Y.end(), y2) - Y.begin();
 
 			if(debug) printf("Removendo o intervalo de [%d, %d] com id = %d\n", y1, y2 - 1, -id);
            length = update(1, 0, Y.size()-1, y1, y2-1, id);
            cnt--;
        }
        if(debug) print_segtree();
        if(debug) cout << endl;
 
        last = x;
    }
 
    printf("%lld\n", ans);
}