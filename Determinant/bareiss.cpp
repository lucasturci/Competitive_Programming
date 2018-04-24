#include <bits/stdc++.h>

/* Calcula o determinante de uma matriz (serve para matriz de doubles tambem) - Algoritmo de Bareiss */

#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 1007;

using namespace std;
typedef long long ll;

int mat[57][57];

int det(int n) {
	int a[57][57];
	int i, j, k;

	/* Copia matriz */
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j) 
			a[i][j] = mat[i][j];

	/* Algoritmo de bareiss */
	for(i = 0; i < n-1; ++i) {
		for(j = i + 1; j < n; ++j) {
			for(k = i + 1; k < n; ++k) {
				a[j][k] = a[j][k]*a[i][i] - a[j][i]*a[i][k];
				if(i) a[j][k] /= a[i-1][i-1];
			}
		}
	}
	return a[n-1][n-1];
}

// Calcula o determinante enquanto escalona a matriz (pois o determinante da matriz escalonada eh o produto de sua diagonal)
int determinant(int n) {
	int i, j, k;
	int t, ans = 1;

	for(i = 0; i < n; ++i) {
		for(j = i+1; j < n; ++j) {
			while(mat[j][i]) {
				ans *= -1;
				t = mat[i][i]/mat[j][i];
				for(int k = i; k < n; ++k) {
					mat[i][k] = (mat[i][k] - mat[j][k]*t);
					mat[i][k] ^= mat[j][k];
					mat[j][k] ^= mat[i][k];
					mat[i][k] ^= mat[j][k];
				}
			}
		}
		if(mat[i][i] == 0) return 0;
		else ans *= mat[i][i];
	}
	
	return ans;
}

int main() {

	int n;
	cin >> n;

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			cin >> mat[i][j];

	cout << determinant(n) << endl;
}