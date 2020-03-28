// Problema C do Yandex Cup 2017, disponivel no grupo do summer school 2020: https://codeforces.com/group/Ohoz9kAFjS/contest/102486/problem/C
#include <bits/stdc++.h>

#define pb push_back
using namespace std;
typedef long long ll;


const int N = 2 * 300007;
struct state {
    int sz, link, firstpos;
    int l, r;
    map<char, int> nxt;
};

int tt, last;
state sa[N]; 

void sa_add(char c) {
    int cur = tt++;
    sa[cur].sz = sa[last].sz+1;
    sa[cur].firstpos = sa[cur].sz-1;
    int p = last;
    while (p != -1 && !sa[p].nxt.count(c)){
        sa[p].nxt[c] = cur;
        p = sa[p].link;
    }
    if(p == -1) sa[cur].link = 0;
    else {
        int q = sa[p].nxt[c];
        if(sa[p].sz+1 == sa[q].sz) {
            sa[cur].link = q;
        }
        else {
            int clone = tt++;
            sa[clone].firstpos = sa[q].firstpos;
            sa[clone].nxt = sa[q].nxt;
            sa[clone].link = sa[q].link;
            sa[clone].sz = sa[p].sz+1;
            while (p != -1 && sa[p].nxt.count(c) && sa[p].nxt[c] == q){
                sa[p].nxt[c] = clone;
                p = sa[p].link;
            }
            sa[q].link = clone;
            sa[cur].link = clone;
        }
    }
    last = cur;
}

void build(string & s) {
    tt = 1;
    last = 0;
    sa[0].sz = 0;
    sa[0].link = -1;

    for(char c : s) {
        sa_add(c);
    }
}

int acc[30][N];

int main() {
    ios::sync_with_stdio(0);

    string s; cin >> s;

    build(s);

    for(int cur = 1; cur < tt; ++cur) {
        sa[cur].l = sa[cur].firstpos - sa[cur].sz+1;
        sa[cur].r = sa[cur].firstpos - (sa[sa[cur].link].sz+1) + 1;
    }

    for(int c = 0; c < 30; ++c) {
        acc[c][0] = s[0] == ('a' +  c);
        for(int i = 1; i < s.size(); ++i) {
            acc[c][i] = acc[c][i-1] + (s[i] == ('a' +  c));
        }
    }

    ll ans = 0;
    for(int u = 1; u < tt; ++u) {
        for(auto aux : sa[u].nxt) {
            char c = aux.first;
            int l = sa[u].l, r = sa[u].r;
            ans += acc[c - 'a'][r] - (l - 1 >= 0? acc[c - 'a'][l-1] : 0);
        }
    }

    for(int u = 1; u < tt; ++u) {
        int v = sa[u].link;
        char c = s[sa[u].r];
        if(sa[u].nxt.count(c)) continue;
        int flag = 0;
        for(auto aux : sa[v].nxt) {
            flag = flag or aux.first == c;
        }
        ans += flag;
    }

    cout << ans << endl;
}