#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


vector<int> LIS(vector<int> v) {
	vector<queue<int> > lis;
	vector<int> aux;

	for(int i = 0; i < v.size(); ++i) {
		int p = lower_bound(aux.begin(), aux.end(), v[i]) - aux.begin();
		if(p == aux.size()) lis.push_back(queue<int>()), aux.push_back(0);
		lis[p].push(v[i]);
		aux[p] = v[i];
	}

	for(int i = 0; i < aux.size(); ++i) {
		aux[i] = lis[i].front();
	}

	return aux;
}
int main() {
	int n;
	cin >> n;
	vector<int> v = vector<int>(n);
	for(int i = 0; i < n; ++i) cin >> v[i];
	vector<int> ans = LIS(v);
	for(int i = 0; i < ans.size(); ++i) cout << ans[i] << " ";
	cout << endl;
}