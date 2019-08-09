#include <bits/stdc++.h>

using namespace std;

// inicializa table = sparse_table<int> (vec, [](int a, int b) {return max(a, b);}); (por exemplo)
template<typename T>
struct sparse_table {
	vector<T> tab[25];
	int n;
	function<T (T, T)> op; // this function has to be 

	sparse_table() {}
	sparse_table(vector<int> & vec, function<T (T, T)> op) {
		this->n = vec.size();
		for(int i = 0; i < 25; ++i) {
			tab[i].resize(n);
		}
		this->op = op;

		tab[0] = vec;
		for(int i = 1; i < 25; ++i) {
			for(int j = 0; j < n; ++j) {
				tab[i][j] = op(tab[i-1][j], tab[i-1][min(n - 1, j + (1 << i-1))]);
			}
		}

	}

	void build(vector<T> & vec, function<T (T, T)> op) {
		*this = sparse_table(vec, op);
	}

	T query(int l, int r) {
		int sz = r - l + 1;
		int j = __builtin_popcount(-1) - __builtin_clz(sz) - 1;
		return op(tab[j][l], tab[j][r - (1 << j) + 1]);
	}
};


int main() {
	sparse_table<int> st;

	vector<int> v = {1, 2, 3, 4};
	st = sparse_table<int>(v, [](int a, int b) {return max(a, b);});
	cout << st.query(0, 2) << endl; 
}