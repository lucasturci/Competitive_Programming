/*
	https://www.hackerrank.com/contests/world-codesprint-6/challenges/functional-palindromes
	IDEA: Build palindromic tree to find all dinstinct palindromes and frequency of them. Sort them using hash lcp, and just two pointers to answer queries

*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

struct node {
	map<int, int> ch; // children
	int link, cnt; // how many times it appears as subtring
	int start; // first time this palindrome appears as subtring. If you want the last, just reverse the string
	int sz; // size of the palindrome
};

const int N = 100007, M = 1e9 + 7;
node _tree[N + 2];
node * tree = _tree + 1;

const int key = 100001;

int build(string & s, bool frequency_of_appearence = false) {
	tree[-1].link = -2;
	tree[-1].sz = -1;
	tree[0].link = -1;
	tree[0].sz = 0;

	int tt = 0;
	int last = -1;

	for(int i = 0; i < s.size(); ++i) {
		char c = s[i];
		// Add a new character
		while(i - tree[last].sz == 0 or s[i - tree[last].sz - 1] != c) last = tree[last].link;

		if(tree[last].ch.count(c) == 0) {
			++tt;

			tree[tt].sz = tree[last].sz + 2;
			tree[tt].cnt = 0;
			tree[tt].start = i - tree[tt].sz + 1;

			tree[last].ch[c] = tt;

			// Finds suffix link
			int u = tree[last].link;
			while(u != -2 and s[i - tree[u].sz - 1] != c) u = tree[u].link;
			tree[tt].link = u == -2? 0 : tree[u].ch[c];
		}

		last = tree[last].ch[c];
		tree[last].cnt++;
		assert(tree[last].link != -2);
		assert(tree[last].start + tree[last].sz <= s.size());
		// cout << "Found palindrome " <<  last << " as " << s.substr(tree[last].start, tree[last].sz) << endl;
	}

	// If you want to calculate frequencies for each palindrome
	if(frequency_of_appearence) {
		for(int i = tt; i > 0; --i) {
			tree[tree[i].link].cnt += tree[i].cnt;
		}
	}

	return tt; // 1 to tt are valid strings
}



int f[N], h[N];
int pot31[N], potKey[N];


string s; 

int query(int l, int r) {
	return (h[r] - ( (ll) pot31[r - l + 1] * (l? h[l-1] : 0) % M) + M)%M;
}

int F(int l, int r) {
	return (f[r] - ( (ll) potKey[r - l + 1] * (l? f[l-1] : 0) % M) + M)%M;
}
bool cmp(int u, int v) {
	int l = 1, r = min(tree[u].sz, tree[v].sz);
	int ans = 0;

	while(l <= r) {
		int mid = (l+r)>>1;

		if(query(tree[u].start, tree[u].start + mid - 1) == query(tree[v].start, tree[v].start + mid - 1)) {
			ans = mid;
			l = mid+1;
		} else {
			r = mid-1;
		}
	}
	if(ans == min(tree[u].sz, tree[v].sz)) return tree[u].sz < tree[v].sz;
	else return s[tree[u].start + ans] < s[tree[v].start + ans];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int ignore, q;
	cin >> ignore >> q;
	cin >> s;

	int hh = 0, ff = 0, p31 = 1, pKey = 1;
	for(int i = 0; i < s.size(); ++i) {
		hh = ll(hh) * 31 % M;
		ff = ll(ff) * key % M;
		hh = (hh + s[i] - 'a' + 1)%M;
		ff = (ff + s[i])%M;
		h[i] = hh;
		f[i] = ff;

		pot31[i] = p31;
		potKey[i] = pKey;
		p31 = (ll) p31 * 31 % M;
		pKey = (ll) pKey * key % M;
	}

	int n = build(s, true); // i have n different palindromes, from 1 to n

	vector<int> vec(n);
	iota(vec.begin(), vec.end(), 1);

	sort(vec.begin(), vec.end(), cmp);

	vector<pair<ll, ll> > queries;
	for(int i = 0; i < q; ++i) {
		ll k; cin >> k;
		queries.emplace_back(k, i);
	}

	sort(queries.begin(), queries.end());
	
	ll cnt = 0;
	for(int j = -1, i = 0; i < q; ++i) {
		while(j + 1 < (int) vec.size() and cnt < queries[i].first) {
			j++;
			cnt += tree[vec[j]].cnt;
		}

		assert(j > -1);
		int ans;
		if(cnt < queries[i].first) ans = -1;
		else {
			// cout << s.substr(tree[vec[j]].start, tree[vec[j]].sz) << endl;
			ans = F(tree[vec[j]].start, tree[vec[j]].start + tree[vec[j]].sz - 1);
		}

		queries[i].first = ans;
		swap(queries[i].first, queries[i].second);
	}

	sort(queries.begin(), queries.end());
	for(auto & [idx, ans] : queries) cout << ans << '\n';
}