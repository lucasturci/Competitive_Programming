#include <bits/stdc++.h>
 
#define fi first
#define se second
#define mp make_pair
#define eb emplace_back
 
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
 
const int N = 2007;
 
int n, k;
char mat[N][N];
int f[N][N], pai[N][N];
 
int adj(int i, int j) {
	if(i < n and j < n) return min(mat[i][j+1], mat[i+1][j]);
	else if(i < n) return mat[i+1][j];
	else return mat[i][j+1];
}
 
vector<ii> diag[N + N];
int pos[N][N];
 
string repeat_as(int x) {
	string ans = "";
	while(x--) ans += 'a';
	return ans;
}
 
string create_string(int i, int j) {
	string ans = repeat_as(i + j - 2);
	ans += mat[i][j];
	while(!(i == n and j == n)) {
		if(i < n and j < n) {
			if(pos[i+1][j] < pos[i][j+1]) i++;
			else j++;
		} else if(i < n) i++;
		else j++;
		ans += mat[i][j];
	}
	return ans;
}
 
int main() {
	memset(f, 0x3f, sizeof f);
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
 
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			cin >> mat[i][j];
			diag[i + j].eb(i, j);
		}
	}
 
	for(int i = n + n - 1; i >= 2; --i) {
		sort(diag[i].begin(), diag[i].end(), [=](ii a, ii b) {
			if(mat[a.fi][a.se] != mat[b.fi][b.se])
				return mat[a.fi][a.se] < mat[b.fi][b.se];
			int p1 = a.fi < n? pos[a.fi+1][a.se] : 0x3f3f3f;
			int p2 = a.se < n? pos[a.fi][a.se+1] : 0x3f3f3f;
			int p = min(p1, p2);
 
			int q1 = b.fi < n? pos[b.fi+1][b.se] : 0x3f3f3f;
			int q2 = b.se < n? pos[b.fi][b.se+1] : 0x3f3f3f;
			int q = min(q1, q2);
 
			return p < q;
		});
 
		for(int j = 0; j < diag[i].size(); ++j) {
			int p, q; tie(p, q) = diag[i][j];
			pos[p][q] = j;
		}
	}
 
	f[1][1] = mat[1][1] != 'a';
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if(i == 1 and j == 1) continue;
			f[i][j] = min(f[i-1][j], f[i][j-1]) +( mat[i][j] != 'a');
		}
	}
 
	vector<vector<ii> > cand(n + n + 1, vector<ii>());
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if(f[i][j] <= k) {
				if(i < n) cand[i + j + 1].eb(i+1, j);
				if(j < n) cand[i + j + 1].eb(i, j+1);
			}
		}
	}

	if(f[n][n] <= k) {
		cout << repeat_as(2 * n - 1) << endl;
		return 0;
	}
 
	vector<string> res;
	for(vector<ii> & vec : cand) {
		int j = 0; 
		if(vec.size() == 0) continue;
		for(int i = 0; i < vec.size(); ++i) {
			int p, q; tie(p, q) = vec[i];
			if(pos[p][q] < pos[vec[j].fi][vec[j].se]) j = i;
		}
		res.eb(create_string(vec[j].fi, vec[j].se));
	}
 
	string ans = create_string(1, 1);
	for(string & x : res) ans = min(ans, x);
	cout << ans << endl;
 
}