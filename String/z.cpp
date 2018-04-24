#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

const int N = 1000007, inf = 0x3f3f3f3f;

int z[N];

int main() {
	ios::sync_with_stdio(false);

	string s;
	cin >> s;

	z[0] = 0;

	int l = 0, r = 0;
	for(int i = 1; i < s.size(); ++i) {
		if(i > r) l = r = i;
		z[i] = min(z[i-l], r - i);

		while(i + z[i] < s.size() and s[i+z[i]] == s[z[i]]) {
		    z[i]++;
		    l = i;
		    r = i + z[i];
		}
		    
	}

	for(int i = 0; i < s.size(); ++i) cout << z[i] << " ";
	cout << endl;

	
}