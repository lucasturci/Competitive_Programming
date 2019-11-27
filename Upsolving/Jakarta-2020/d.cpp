#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define eb emplace_back

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int N = 200007, inf = 0x3f3f3f3f;

int R, C;
int n;

char mat[507][507];
string str[N];

struct query {
	int l1, r1, l2, r2;
	int id; // id da string
};

vector<int> suffix_array(string & s) {
	int n = s.size();

	vector<int> a(n), c(n), a1(n), c1(n);
	int l = 1;

	iota(a.begin(), a.end(), 0);
	sort(a.begin(), a.end(), [](int i, int j) {
		return s[i] < s[j];
	});

	c[a[0]] = 0;
	for(int i = 1; i < n; ++i) {
		if(s[a[i]] == s[a[i-1]]) c[a[i]] = c[a[i-1]];
		else c[a[i]] = c[a[i-1]] + 1;
	}

	while(l < n) {
		vector<int> head(n);

		for(int i = 0; i < n; ++i) {
			head[c[a[i]]]++;
		}

		for(int i = 1; i < n; ++i) {
			head[i] += head[i-1];
		}

		for(int i = n-1; i >= 0; --i) {
			int j = (a[i] - l + n)%n;
			int x = c[j];
			head[x]--;
			a1[head[x]] = j;
		}

		// recalcula cores

		c1[a1[0]] = 1;
		for(int i = 1; i < n; ++i) {
			if(c[a1[i]] == c[a1[i-1]] and c[(a1[i] + l)%n] == c[(a1[i-1] + l)%n]) c1[a1[i]] = c[a1[i-1]];
			else c1[a1[i]] = c1[a1[i-1]] + 1;
		}

		a = a1;
		c = c1;
		l <<= 1;
	}

	return a;
}

// returns -1 if less, 0 if equal and 1 if greater 
int comp_string(string & s, int j, vector<int> & sa, string & t) {
	j = sa[j];
	int n = t.size();
	for(int i = 0; i < s.size(); ++i) {
		if(s[i] < t[(j + i)%n]) return -1;
		if(s[i] > t[(j + i)%n]) return 1;
	}

	return 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> R >> C >> n;

	string s1, s2;
	for(int i = 0; i < R; ++i) {
		for(int j = 0; j < C; ++j) {
			cin >> mat[i][j];
			s1 += mat[i][j];
		}
		s1 += '$';
	}

	for(int j = 0; j < C; ++j) {
		for(int i = 0; i < R; ++i) {
			s2 += mat[i][j];
		}
		s2 += '$';
	}

	for(int i = 0; i < n; ++i) {
		cin >> str[i];
	}

	vector<int> sa1, sa2;
	sa1 = suffix_array(s1);
	sa2 = suffix_array(s2);

	vector<int> pos1(sa1.size()), pos2(sa2.size());

	for(int i = 0; i < sa1.size(); ++i) {
		pos1[sa1[i]] = i;
	}

	for(int i = 0; i < sa2.size(); ++i) {
		pos2[sa2[i]] = i;
	}


	vector<query> queries;
	for(int i = 0; i < n; ++i) {
		string & s = str[i];
		vector<query> aux(s.size());
		
		int l = -1, r = -1; // l e r atuais do sa2 (porque agora estou calculando sa2)
		
		int lo = 0, hi = sa2.size()-1;
		
		while(lo <= hi) {
			int mid = (lo + hi)/2;
			int ret = comp_string(s, mid, sa2, s2);
			if(ret == -1) hi = mid-1;
			else if(ret == 1) lo = mid+1;
			else if(ret == 0) {
				hi = mid-1;
				l = mid;
			}
		}

		lo = 0, hi = sa2.size()-1;
		while(lo <= hi) {
			int mid = (lo + hi)/2;
			int ret = comp_string(s, mid, sa2, s2);
			if(ret == -1) hi = mid-1;
			else if(ret == 1) lo = mid+1;
			else if(ret == 0) {
				lo = mid+1;
				r = mid;
			}
		}

		for(int j = 0; j < s.size(); ++j) {
			aux[j].l1 = l;
			aux[j].r1 = r;
			l = pos[(sa2[l] + 1)%n];
		}
	}




}