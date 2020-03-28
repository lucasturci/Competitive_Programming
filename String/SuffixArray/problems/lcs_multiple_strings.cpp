/* IMPORTANT!!!! THIS CODE IS NOT READY YET */
#include <bits/stdc++.h>

#define fi first
#define se second

using namespace std;

vector<int> suffix_array(string & s) {
    s += '$';
    int n = s.size();
    vector<int> a(n), c(n);
    vector<int> a2(n), c2(n);

    int len = 1;

    iota(a.begin(), a.end(), 0);
    sort(a.begin(), a.end(), [=](int a, int b) {
        return s[a] < s[b];
    });

    int col = 0;
    c[0] = 0;
    for(int i = 1; i < n; ++i) {
        if(s[a[i]] != s[a[i-1]]) col++;
        c[a[i]] = col;
    }

    while(len < n) {

        vector<int> cnt(n, 0);
        for(int i = 0; i < n; ++i) cnt[c[a[i]]]++;
        for(int i = 1; i < n; ++i) cnt[i] += cnt[i-1];
        for(int i = n-1; i >= 0; --i) {
            int j = (a[i] - len + n)%n;
            a2[ --cnt[c[j]] ] = j;
        }

        int col = 0;
        c2[0] = col;
        for(int i = 1; i < n; ++i) {
            if(c[a2[i]] != c[a2[i-1]] or c[(a2[i] + len)%n] != c[(a2[i-1] + len)%n]) col++;
            c2[a2[i]] = col;
        }

        a = a2;
        c = c2;
        len <<= 1;
    }

    return a;
}

vector<int> build_lcp(vector<int> & a, string & s) {
    int n = a.size();

    vector<int> lcp(n), pos(n);

    for(int i = 0; i < n; ++i) {
        pos[a[i]] = i;
    }

    int sz = 0;
    for(int i = 0; i < n; ++i) {
        if(pos[i] + 1 == n) {
            sz = 0;
            continue;
        } 
        int j = a[pos[i] + 1];
        while(i + sz < n and j + sz < n and s[i + sz] == s[j + sz]) sz++;
        lcp[i] = sz;
        if(sz) sz--;
    }

    return lcp;
}

struct min_stack {
    stack<pair<int, int > > st;

    void push(int x) {
        int cur = x;
        if(st.size()) cur = min(cur, st.top().se);

        st.push(make_pair(x, cur));
    }

    void pop() {
        st.pop();
    }

    pair<int, int> top() {
        return st.top();
    }

    int size() {
        return st.size();
    }
};

struct min_queue {
    min_stack a, b;

    void push(int x) {
        b.push(x);
    }

    void pop() {
        if(a.size() == 0) {
            while(b.size()) a.push(b.top().fi), b.pop();
        }
        if(a.size()) a.pop();
    }

    int men() {
        return min(a.size()? a.top().se : 0x3f3f3f3f, b.size()? b.top().se : 0x3f3f3f3f);
    }

    int size() {
        return a.size() + b.size();
    }
};

int n, m;
int cnt[2];

int tot;
void add(int x) {
    int p = x > n;
    if(cnt[p] == 0) tot++;
    cnt[p]++;
}

void remove(int x) {
    int p = x > n;
    cnt[p]--;
    if(cnt[p] == 0) tot--;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s, t;
    cin >> s >> t;

    n = s.size(), m = t.size();
    string x = s + "$" + t + "$";

    vector<int> a = suffix_array(x);
    vector<int> lcp = build_lcp(a, x);

    min_queue q;

    add(a[2]);

    int ans = 0;
    for(int j = 3, i = 2; i < x.size(); ++i) {
        // adiciona quantos precisa
        while(j < n and tot < 2) {
            add(a[j]);
            if(j-1 >= i) q.push(lcp[j-1]);
            j++;
        } 
        if(tot == 2) ans = max(ans, q.men());

        if(j >= i + 1) q.pop();
        remove(a[i]);
    }

    cout << ans << endl;

}