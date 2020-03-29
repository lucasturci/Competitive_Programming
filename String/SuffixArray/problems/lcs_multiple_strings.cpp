/* IMPORTANT!!!! THIS CODE IS NOT READY YET */
#include <bits/stdc++.h>

#define fi first
#define se second
#define pb push_back

using namespace std;

vector<int> suffix_array(string & s) {
    s += '$';
    int n = s.size();
    vector<int> a(n), c(n);
    vector<int> a2(n), c2(n);

    int len = 1;

    iota(a.begin(), a.end(), 0);
    sort(a.begin(), a.end(), [&](int a, int b) {
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
        if(pos[i] + 1 == n) continue;    
        int j = a[pos[i] + 1];
        while(i + sz < n and j + sz < n and s[i + sz] == s[j + sz] and s[i + sz] != '$') sz++;
        lcp[pos[i]] = sz;
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

void _solve() {
    int n; cin >> n;

    vector<int> id, cnt(n, 0);

    string x = "";
    for(int i = 0; i < n; ++i) {
        string s; cin >> s;
        x += s;
        while(id.size() < x.size()) id.pb(i);
        if(i + 1 < n) {
            x += '$';
            id.pb(-1);
        }
    }

    vector<int> a = suffix_array(x);
    vector<int> lcp = build_lcp(a, x);

    min_queue q;

    int tot = 0;
    auto add = [&](int p) {
        int x = id[p];
        if(cnt[x] == 0) tot++;
        cnt[x]++;
    };

    auto remove = [&](int p) {
        int x = id[p];
        cnt[x]--;
        if(cnt[x] == 0) tot--;
    };

    add(a[n]);

    int ans = 0;
    for(int j = n+1, i = n; i < x.size(); ++i) {
        // adiciona quantos precisa
        while(j < x.size() and tot < n) {
            add(a[j]);
            if(j-1 >= i) q.push(lcp[j-1]);
            j++;
        } 
        if(tot == n) ans = max(ans, q.men());

        if(j >= i + 1) q.pop();
        remove(a[i]);
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int t; cin >> t;

    while(t--) {
        _solve();
    }


}