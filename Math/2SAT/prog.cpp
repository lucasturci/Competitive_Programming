/*
	Esse programa recebe como entrada uma formula booleana f, por exemplo:
		f = (x1 | x2) & (x3 | x1) & (x3 | x5) & (x2 | x4),
	em que x_i (1 <= i <= 5) sao as variaveis booleanas, e o objetivo do programa eh encontrar
	valores para essas variaveis de modo que f seja true.

	Para que f seja true, cada termo entre parenteses deve ser true, logo temos que satisfazer cada termo.
	Cada termo entre parenteses pode ser escrito como uma implicacao, pelo seguinte lema:
	[ ~a => b ] <=> [ a | b ]
	
	Logo [ x1 | x2 ] pode ser escrito como [ ~x1 => x2 ], [ x3 | x1 ] pode ser escrito como [ ~x1 => x3 ] etc.
	
	As implicacoes sao transitivas, entao se a => b e b => c, entao a => c. Vamos denotar as implicacoes derivadas de transitividade por '==>'. 
	Entao nesse caso a ==> c

	Solucao:
		Se existir alguma serie de implicacoes tal que [ a ==> ~a & ~a ==> a ], entao isso eh equivalente a [ (~a | ~a) & (a | a) ] <=> [a & ~a] <=> 0
		Logo, podemos dizer que f nao tem solucao. Com outras palavras, se a e ~a estiverem no mesmo componente conexo (formarem um ciclo) 
		entao f nao tem solucao

		Caso contrario, em uma ordenacao topologica das arestas de implicacao, temos ou a ==> ~a, ou ~a ==> a. 
			O primeiro caso equivale a [ ~a | ~a ]. Escolhemos a = 0
			O segundo caso equivale a [a | a]. Escolhemos a = 1

	Fazendo isso para todas as variaveis, encontramos uma solucao possivel para f
*/

#include <bits/stdc++.h>

using namespace std;

int n, m;
const int N = 100007;

int vis[N+N], col[N+N], cnt[N+N], tim[N+N];
vector<int> topo, e[N+N], rev[N+N];

void dfs(int u) {
	vis[u] = 1;

	for(int v : e[u])
		if(vis[v] == 0) dfs(v);

	topo.push_back(u);
}

void colorfy(int u, int c) {
	col[u] = c;
	cnt[c]++;
	for(int v : rev[u])
		if(col[v] == 0) colorfy(v, c);
}

int t;
void dfs2(int u) {
	vis[u] = 1;
	cnt[col[u]]--;

	for(int v : e[u])
		if(vis[v] == 0) dfs2(v);
	if(cnt[col[u]] == 0) tim[col[u]] = ++t;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	// n = numero de variaveis m = numero de termos da formula de f
	cin >> n >> m;

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		int na = a < 0, nb = b < 0;

		if(na) a = -a;
		if(nb) b = -b;
		e[2 * a + !na].push_back(2 * b + nb);
		rev[2 * b + nb].push_back(2 * a + !na);
		e[2 * b + !nb].push_back(2 * a + na);
		rev[2 * a + na].push_back(2 * b + !nb);
	}


	for(int u = 2; u <= 2*n+1; ++u)
		if(vis[u] == 0)
			dfs(u);

	reverse(topo.begin(), topo.end());
	
	int c = 0;
	for(int u : topo)
		if(col[u] == 0)
			colorfy(u, ++c);


	for(int i = 1; i <= n; ++i) {
		if(col[2*i] == col[2*i+1]) {
			cout << "NO\n";
			return 0;
		}
	}

	topo.clear();
	memset(vis, 0, sizeof vis);
	for(int u = 2; u <= 2 * n + 1; ++u)
		if(vis[u] == 0) dfs2(u);

	for(int u = 1; u <= n; ++u) {
		if(tim[col[2*u+1]] < tim[col[2*u]]) cout << 0 << " ";
		else cout << 1 << " ";
	}
	cout << '\n';
}
