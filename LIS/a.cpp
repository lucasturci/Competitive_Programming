#include <bits/stdc++.h>

#define mp make_pair
#define fi first
#define se second

using namespace std;

int v[100007], pred[100007];

int main() {
	int n;
	set<pair<int, int> > s;

	cin >> n;

	for(int i = 0; i < n; ++i) cin >> v[i];

	s.insert(mp(v[0], 0));
	pred[0] = -1;
	for(int i = 1; i < n; ++i) {
		pair<int, int> x = mp(v[i], i);
		set<pair<int, int> >::iterator it = s.lower_bound(mp(x.fi, -1));
		if(it == s.end()) {
			pred[i] = (*s.rbegin()).se;
			s.insert(x);
		}
		else {
			if(it == s.begin()) pred[i] = -1;
			else {
				it--;
				pred[i] = it->se;
				it++;
			}
			s.erase(it);
			s.insert(x);
		}

	}
	pair<int, int> x = (*s.rbegin());
	for(int p = x.se; p != -1; p = pred[p]) {
		cout << v[p] << " ";
	}
	cout << endl;


	return 0;
}