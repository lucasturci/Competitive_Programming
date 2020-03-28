#include <bits/stdc++.h>

// Retorna um vetor com os indices de inicio de prefixo.
// Cuidado, essa funcao adiciona um caractere $ no final da string
vector<int> build_sufix_array(string & s) {
	s += '$';
	int n = s.size();
	vector<int> head(n), a(n), a1(n), c(n), c1(n);

	for(int i = 0; i < n; ++i) a[i] = i;
	sort(a.begin(), a.end(), [&](int i, int j) {
		return s[i] < s[j];
	});
	int cc = 0;
	for(int i = 0; i < n; ++i) {
		if(i == 0 or s[a[i]] != s[a[i-1]]) {
			c[a[i]] = cc; 
			head[cc++] = i;
		} else c[a[i]] = c[a[i-1]];
	}

	int l = 1, i, j;
	while(l < n) {
		for(i = 0; i < n; ++i) {
			j = (a[i] - l + n)%n;
			a1[head[c[j]]++] = j;
		}
		cc = 0;

		head.assign(head.size(), 0);
		for(i = 0; i < n; ++i) {
			if(i == 0 or c[a1[i]] != c[a1[i-1]] or c[(a1[i] + l)%n] != c[(a1[i-1] + l)%n]) {
				head[cc] = i;
				c1[a1[i]] = cc++;
			} else c1[a1[i]] = c1[a1[i-1]];
		}

		a.assign(a1.begin(), a1.end());
		c.assign(c1.begin(), c1.end());
		l <<= 1;
	}

	return a;
}

int main() {

}