#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

const int N = 1000007, inf = 0x3f3f3f3f;


int pi[N];

int main() {
	ios::sync_with_stdio(false);

	string s;
	cin >> s;

	pi[0] = 0;

	for(int i = 1; i < s.size(); ++i) {

		pi[i] = pi[i-1];
		while(pi[i] > 0 and s[i] != s[pi[i]]) {
			pi[i] = pi[pi[i] - 1];
		}

		if(s[i] == s[pi[i]]) pi[i]++;
	}

	for(int i = 0; i < s.size(); ++i) {
		cout << pi[i] << " ";
	}

	cout << endl;

	
}