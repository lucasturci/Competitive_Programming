#include <bits/stdc++.h>

#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 1000007;

struct no {
    int suf, len;
    map<char, int> g;
};

no sa[N];
int vis[N];
int f[N]; // how many different paths starting at u, which corresponds to how many different substrings this state can generate

int tt, last;

void sa_add(char c) {
    int cur = ++tt;

    sa[cur].len = sa[last].len + 1;
    int p;
    for(p = last; p != -1; p = sa[p].suf) {
        if(sa[p].g.count(c)) break;
        sa[p].g[c] = cur;
    }

    if(p == -1) {
        sa[cur].suf = 0;
    } else {
        int q = sa[p].g[c];
        if(sa[q].len == sa[p].len + 1) {
            sa[cur].suf = q;
        } else {
            int clone = ++tt;
            sa[clone].len = sa[p].len + 1;
            sa[clone].g = sa[q].g;
            sa[clone].suf = sa[q].suf;

            while(p != -1 and sa[p].g.count(c) and sa[p].g[c] == q) {
                sa[p].g[c] = clone;
                p = sa[p].suf;
            }

            sa[q].suf = clone;
            sa[cur].suf = clone;

        }
    }

    last = cur;
}

void build(string & s) {
    sa[0].suf = -1;
    sa[0].len = 0;

    for(char c : s) {
        sa_add(c);
    }
}

// calculate how many different paths starting at u, which corresponds to how many different substrings this state can generate
void calc(int u) {
    if(vis[u]) return;
    vis[u] = 1;

    f[u] = 1;
    for(auto aux : sa[u].g) {
        int v = aux.se;
        calc(v);
        f[u] += f[v];
    }

}


// returns the kth least substring if all DISTINCT substrings of s are sorted
string kth(int k) {
    if(k <= 0) throw runtime_error("K < 0");
    string ans;
    k++; // if k was 1 we would print the empty string, so we sum 1 to k to avoid that
    int u = 0;
    while(k != 1) {
        k --;
        int aux = u;
        for(auto aux : sa[u].g) {
            char c; int v;
            tie(c, v) = aux;
            if(f[v] >= k) {
                ans += c;
                u = v;
                break;
            }
            k -= f[v];
        }
        if(u == aux and k > 0) throw runtime_error("K is too large");
    }
    return ans;
}



int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    build(s);

    calc(0);
    int t; cin >> t;
    while(t--) {
        int k; cin >> k;
        cout << kth(k) << '\n';
    }
}