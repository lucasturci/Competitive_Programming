#include <bits/stdc++.h>

/*
Alien Trick

Geralmente aparece em problemas que:
	- Quero minimizar uma função e a função é decrescente com o parametro
	- Quero maximiar a função e a função crescente com o parametro
Nao tenho certeza se isso é necessario pra monotonicidade

Restrição importante:
	As restricoes abaixo podem ser resumidas em: "Cada aumento do parametro é menos util do que o aumento anterior"
	- Se quero maximizar, a funcao tem que ser concava. Isto é, sua derivada decresce com k
	- Se quero minimizar, a funcao tem que ser convexa. Isto é, sua derivada cresce com k

Detalhes de implementacao:
Se a funcao eh nos inteiros, lambda pode ser procurado nos inteiros
Eu acho que lambda deve ser procurado no intervalo [0, maior valor que posso somar em uma iteracao da dp]

Lembra de somar ou subtrair na resposta final (lambda * k), mas dessa vez o k realmente do input, não o que foi encontrado!!

Se a restricao é do tipo <= k, faz a DP minimizando o k utilizado.
Pra restricao do tipo exatamente k:
Se voce garantir que a função é concava/convexa, não sei se precisa mudar a solução, mas da pra fazer a DP minimizando e depois maximizando
o k pra achar o intervalo de k's pra um certo lambda

*/

#define fi first
#define se second
using namespace std;
typedef long long ll;

const int N = 2007;

double p[N], u[N], pu[N];

int caso = 0;
int vis[N][N];
pair<double, int> f[N][N];
double l;

inline pair<double, int> soma(pair<double, int> a, pair<double, int> b) {
	return make_pair(a.fi + b.fi, a.se + b.se);
}

// Calcula DP sem a restricao de b, minimizando a quantidade de b's usada
pair<double, int> solve(int n, int a) {
	pair<double, int> zero;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j <= a; ++j) {
			f[i][j] = (i? f[i-1][j] : zero);
			if(j) f[i][j] = max(f[i][j], soma(i? f[i-1][j-1] : zero, {p[i], 0} ));
			f[i][j] = max(f[i][j], soma(i? f[i-1][j] : zero, {u[i] - l, -1}));
			if(j) f[i][j] = max(f[i][j], soma(i? f[i-1][j-1] : zero, {pu[i] - l, -1} ));
		}
	}
	return f[n-1][a];

}

// Calcula a funcao lagrangiana 
pair<double, int> poke(int n, int a, double lambda) {
	double ret;
	int b;
	l = lambda;
	tie(ret, b) = solve(n, a);
	return make_pair(ret, -b);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, a, b; cin >> n >> a >> b;

	for(int i = 0; i < n; ++i) cin >> p[i];
	for(int i = 0; i < n; ++i) cin >> u[i];
	for(int i = 0; i < n; ++i) pu[i] = p[i] + u[i] - p[i] * u[i];

	double l = 0, r = 1;
	int cnt = 50;
	double mid;
	while(cnt--) {
		mid = (l + r)/2;
		if(poke(n, a, mid).se > b) {
			l = mid;
		} else {
			r = mid;
		}
	}

	cout << poke(n, a, r).fi + b * r << endl;
}