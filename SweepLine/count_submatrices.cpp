// https://cses.fi/problemset/task/1148/

#include <bits/stdc++.h>

/*

	Uma extensão do problema de maior retangulo de zeros, que tambem é resolvido com a tecnica de histograma e cartesian tree.
	Com algumas observações e continhas a mais, da pra calcular pra cada par (width, height), quantas submatrizes
	de zeros com essas dimensoes existem.

	Relembrando, a técnica do histograma fixa cada linha i da matriz e nesse momento 
	hist[j] = altura da coluna j até o próximo 1 acima. Então, a cartesian tree serve pra calcular, pra cada j,
	a largura e altura do maior retangulo em (i, j). 
	A ideia é ir pegando o menor e ir dividindo pra esquerda e direita.

	Duas observações são necessárias pra estender a ideia pra resolver esse problema:
	- Na cartesian tree, quando quebramos pra direita ou esquerda em j, todos os retangulos que 
	couberem na esquerda ou direita com altura menor ou igual do que hist[j] já foram contados. Então a cada momento
	calculamos o número de submatrizes pra um intervalo de alturas.
	- Fixado uma altura, ans[w][h] só difere de ans[w+1][h] por causa de deslocamentos ou de momentos em que w é a 
	largura máxima. Observando melhor alguns casos, ans[w][h] = ans[w+1][h] + número de vezes que algum w2 >= w aparece 
	como largura máxima para este h.	

*/

#define fi first
#define se second
#define eb emplace_back
#define pb push_back

using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

const int N = 1007;

char mat[N][N];

int hist[N]; // histograma

int L[N], R[N];
ll ans[N][N];

// monta cartesian tree
int buildCartesian(int m) {
	stack<ii> st;
	L[0] = R[0] = 0;
	st.emplace(0, 0);
	for(int i = 1; i <= m; ++i) {
		// acha o pai
		while(st.top().fi > hist[i]) st.pop();

		int node = st.top().se;
		L[i] = R[node];
		R[i] = 0;
		R[node] = i;
		st.emplace(hist[i], i);
	}
	return R[0];
}

void solve(int cur, int l, int r, int h0) {
	if(cur == 0) return;

	// coloca de h0 até hist[cur]
	ans[h0][r - l + 1]++;
	ans[hist[cur]+1][r - l + 1]--;

	solve(L[cur], l, cur-1, hist[cur]+1);
	solve(R[cur], cur+1, r, hist[cur]+1);
}

int main() {
	int n, m; cin >> n >> m;

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			cin >> mat[i][j];
		}
	}

	for(int i = 1; i <= n; ++i) {
		// atualiza histograma
		for(int j = 1; j <= m; ++j) {
			hist[j]++;
			if(mat[i][j] == '*') hist[j] = 0;
		}
		int root = buildCartesian(m);
		solve(root, 1, m, 1);
	}


	// propaga os intervalos de h
	for(int j = 1; j <= m; ++j) {
		int sum = 0;
		for(int i = 1; i <= n; ++i) {
			sum += ans[i][j];
			ans[i][j] = sum;
		}
	}

	// usa o fato que ans[w][h] = ans[w+1][h] + todas os blocos que cabem w+1
	for(int i = 1; i <= n; ++i) {
		int cnt = 0;
		ll sum = 0;
		for(int j = m; j >= 1; --j) {
			cnt += ans[i][j];
			sum += cnt;
			ans[i][j] = sum;
		}
	}

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			cout << ans[i][j] << ' ';
		}
		cout << '\n';
	}
}