// problem link: https://codeforces.com/contest/235/problem/C
/* Idea:
    Go through all of the cyclic shifts of the query string and sum how many times it appears in the text. 
    Some cyclic shifts may be equal, and the answer to them must be counted only once. To solve that,
    use hash (or suffix array)
*/

#include <bits/stdc++.h>
 
#define fi first
#define se second
#define eb emplace_back
#define pb push_back
 
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
 
const int N = 1000007;
 
struct state {
    int suf, len, cnt, clone;
    int g[27];
};
 
int tt, last;
state sa[N + N];
 
const ll M = 1e18 + 9;
 
const ll A = 1009;
ll h[N], p[N];
 
ll mult(ll a, ll b)
{
	ll q = (long double)a * b/M;
	ll r = a*b - q*M;
	while (r < 0) r += M;
	while (r >= M) r -= M;
	return r;
}
 
ll get(int l, int r)
{
	if(l == 0) return h[r];
	return (h[r] - mult(h[l-1], p[r-l+1])%M + M)%M;
}
 
void sa_add(char c) {
    int cur = ++tt;
 
    sa[cur].len = sa[last].len + 1;
    int p;
    for(p = last; p != -1; p = sa[p].suf) {
        if(sa[p].g[c - 'a']) break;
        sa[p].g[c - 'a'] = cur;
    }
 
    if(p == -1) {
        sa[cur].suf = 0;
    } else {
        int q = sa[p].g[c - 'a'];
        if(sa[q].len == sa[p].len + 1) {
            sa[cur].suf = q;
        } else {
            int clone = ++tt;
            memcpy(sa[clone].g, sa[q].g, sizeof sa[q].g);
            sa[clone].suf = sa[q].suf;
            sa[clone].len = sa[p].len + 1; 
 
            for(; p != -1 and sa[p].g[c - 'a'] == q; p = sa[p].suf) {
                sa[p].g[c - 'a'] = clone;
            }
 
            sa[cur].suf = clone;
            sa[q].suf = clone;
        }
    }
 
    last = cur;
    sa[cur].cnt = 1;
}
 
void build(string & s) {
    sa[0].suf = -1;
    sa[0].len = 0;
 
    for(char c : s) sa_add(c);
}
 
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
 
    build(s);
 
    vector<int> id(tt + 1, 0);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [](int i, int j) {
        return sa[i].len > sa[j].len;
    });
 
    for(int j : id) {
        if(j) sa[sa[j].suf].cnt += sa[j].cnt;
    }
 
    // for(int i = 0; i <= tt; ++i) {
    //     cout << i << " tem link pra " << sa[i].suf << endl;
    //     cout << " e aparece " << sa[i].cnt << " vezes \n";
    //     if(sa[i].clone) cout << "CLONEEE\n";
    //     cout << "transicoes: " << endl;
        
    //     for(auto aux : sa[i].g) {
    //         cout << i << " vai pra " << aux.second << " por " << aux.fi << '\n';
    //     }
    //     cout << endl;
    // }
 
 
    int q; cin >> q;
 
    while(q--) {
        string t; cin >> t;
 
        int n = t.size();
        t += t;
 
        p[0] = 1ll;
        h[0] = t[0];
        for(int i = 1; i < t.size(); ++i) {
            h[i] = (t[i] + mult(h[i-1], A))%M;
            p[i] = mult(p[i-1], A)%M;
        }
 
        ll ans = 0;
        int l = 0, r = 0;
        int cur = 0;
        unordered_map<ll, bool> vis;
        while(l < n) {
            while(sa[cur].g[t[r] - 'a'] and r - l < n) { // enquanto da pra adicionar e o tamanho nao ta bom ja
                cur = sa[cur].g[t[r] - 'a'];
                r++;
            }
 
            ll aux = get(l, r-1);
            if(r - l == n and vis[aux] == 0) {
                vis[aux] = true;
                ans += sa[cur].cnt;
            }
            if(cur == 0) break;
            // vai andando suffix links ate dar pra encontrar o proximo
            do {
                int new_size = r - l - 1;
                if(new_size <= sa[sa[cur].suf].len) {
                    cur = sa[cur].suf;
                }
                l++;
            } while(cur != -1 and l < n and l < r and !sa[cur].g[t[r] - 'a']);
            if(cur == -1) break;
        }
        cout << ans << '\n';
    }
 
}