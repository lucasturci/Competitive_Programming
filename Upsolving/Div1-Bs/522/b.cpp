#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define eb emplace_back

const int N = 107, inf = 0x3f3f3f3f;

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const int M1 = 1000000007, M2 = 1000000009;

// numero que soma mod dois outros numeros
struct num {
	int x, y;
	num(): x(0), y(0) {}

	num(int a) {
		x = y = a;
	}

	num(int a, int b) {
		x = a, y = b;
	}

	num operator + (num a) {
		return {(x + a.x)%M1, (y + a.y)%M2};
	}

	num operator + (int a) {
		return (*this) + num(a);
	}

	num operator - (num a) {
		return {(x - a.x + M1)%M1, (y - a.y + M2)%M2};
	}

	num operator - (int a) {
		return (*this) - num(a);
	}

	bool operator == (num a) const {
		return x == a.x and y == a.y;
	}

	bool operator != (int a) const {
		return !((*this) == a);
	}
};

int a[N];
int freq[N];
num f[N * N][N]; // f[x][y] = consegue chegar em x, com y items
num g[N * N][N];

num nchoosek[N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	for(int i = 0; i < N; ++i) {
		for(int j = 0; j <= i; ++j) {
			if(i and j) nchoosek[i][j] = nchoosek[i-1][j] + nchoosek[i-1][j-1];
			else nchoosek[i][j] = 1;
		}
	}

	set<int> st;
	int n; cin >> n;

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		freq[a[i]]++;
		st.insert(a[i]);
	}

	if(st.size() == 2) {
		cout << n << endl;
		return 0;
	}



	sort(a, a + n);

	// calcula quantos formas de fazer valor x com y itens
	f[0][0] = 1;
	for(int i = 0; i < n; ++i) {
		for(int x = N * N-1; x >= 0; --x) {
			for(int y = 1; y <= n; ++y) {
				if(x - a[i] >= 0 and y) f[x][y] = f[x][y] + f[x - a[i]][y-1];
			}
		}
	}

	for(int r, l = 0; l < n; l = r) {
		r = l;
		while(r < n and a[l] == a[r]) r++;
		int sum = 0;
		for(int i = l; i < r; ++i) {
			sum += a[i];
			int cnt = i - l + 1;
			g[sum][cnt] = g[sum][cnt] + nchoosek[freq[a[i]]][cnt];
		}
	}

	vector<int> cand;
	int best = 1;
	for(int i = 0; i < N * N; ++i) {
		for(int j = 1; j <= n; ++j) {
			if(f[i][j] == g[i][j] and f[i][j] != 0) {
				// soma i com j itens eh uma possibilidade
				int val = i/j;
				if(freq[val] >= j) {
					best = max(best, j);
					if(j == freq[val] and st.size() == 2) best = n;
				}
			}
		}
	}

	cout << best << endl;

}