#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 1000007;

struct no {
    int suf, len;
    map<char, int> g;
};

no sa[N];
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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    build(s);
}