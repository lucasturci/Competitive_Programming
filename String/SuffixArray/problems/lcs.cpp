/* https://www.codechef.com/problems/SSTORY */
#include <bits/stdc++.h>

using namespace std;

vector<int> suffix_array(string & s) {

	s += '$';
	int n = s.size();
	vector<int> head(n), a(n), a1(n), c(n), c1(n);

	for(int i = 0; i < n; ++i) a[i] = i;
	sort(a.begin(), a.end(), [&](int const & a, int const & b) {
        return s[a] < s[b];
    });

	int cc = 0;
	for(int i = 0; i < n; ++i) {
		if(i == 0 or s[a[i]] != s[a[i-1]]) {
			c[a[i]] = cc; 
			head[cc++] = i;
		} else c[a[i]] = c[a[i-1]];
	}

	int l = 1, i, j;
	while(l < n) {
		for(i = 0; i < n; ++i) {
			j = (a[i] - l + n)%n;
			a1[head[c[j]]++] = j;
		}
		cc = 0;

		head.assign(head.size(), 0);
		for(i = 0; i < n; ++i) {
			if(i == 0 or c[a1[i]] != c[a1[i-1]] or c[(a1[i] + l)%n] != c[(a1[i-1] + l)%n]) {
				head[cc] = i;
				c1[a1[i]] = cc++;
			} else c1[a1[i]] = c1[a1[i-1]];
		}

		a.assign(a1.begin(), a1.end());
		c.assign(c1.begin(), c1.end());
		l <<= 1;
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
        while(i + sz < n and j + sz < n and s[i + sz] == s[j + sz] and s[i+sz] != '$') sz++;
        lcp[pos[i]] = sz;
        if(sz) sz--;
    }

    return lcp;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s, t;
    cin >> s >> t;

    int n = s.size(), m = t.size();
    string x = s + "$" + t;

    vector<int> a = suffix_array(x);
    vector<int> lcp = build_lcp(a, x);

    /* The recovery of the answer implementation was made by rodz */
    int ans = 0;
    for (int i = 0; i+1 < x.size(); i++)
    {
        if (a[i] < s.size() and a[i+1] > s.size())
            ans = max(ans, lcp[i]);
        if (a[i] > s.size() and a[i+1] < s.size())
            ans = max(ans, lcp[i]);
    }
 
    if (ans == 0) {
        cout << 0 << endl;
        return 0;
    }
    int pans = 0x3f3f3f3f; 
   
    int lc = 0;
    for (int i = 0; i < x.size(); i++)
    {
        if (a[i] < s.size())
            lc = lcp[i];
        else if (a[i] > s.size())
        {
            if (lc == ans)
                pans = min(pans, a[i]);
        }
        lc = min(lc, lcp[i]);
    }
    lc = 0;
    for (int i = (int)x.size()-1; i > 0; i--)
    {
        if (a[i] < s.size())
            lc = lcp[i-1];
        else if (a[i] > s.size())
        {
            if (lc == ans)
                pans = min(pans, a[i]);
        }
        lc = min(lc, lcp[i-1]);
    }
    assert(pans != 0x3f3f3f3f);
    cout << x.substr(pans, ans) << '\n';
    cout << ans << '\n';

}