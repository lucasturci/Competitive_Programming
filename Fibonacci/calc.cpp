#include <bits/stdc++.h>

#define M 5

using namespace std;
typedef long long ll;

int mat[2][2], aux[2][2], res[2][2];

/* Multiplica duas matrizes de tamanho 2 */
void mult(int a[2][2], int b[2][2]) {
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			aux[i][j] = 0;
			for(int k = 0; k < 2; ++k) {
				aux[i][j] += a[i][k] * b[k][j];
				aux[i][j] %= M;
			}
		}
	}
	memcpy(a, aux, sizeof aux);
}

ll fib(int n) {

	/* Matriz da operacao */
	mat[0][0] = 0;
	mat[0][1] = mat[1][0] = mat[1][1] = 1;

	res[0][0] = res[1][1] = 1; //matriz identidade

	while(n) {
		if(n&1) mult(res, mat);

		mult(mat, mat);
		n >>= 1;
	}

	return res[0][1];
}

int main() {
	ll n;
	cin >> n;

	cout << fib(n) << endl;

}