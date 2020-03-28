// https://codeforces.com/contest/1086
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;

	while(t--) {
		int k; cin >> k;

		set<int> st;
		for(int i = 0; i < k; ++i) {
			st.insert(i);
		}

		vector<int> ans(k, -1);
		string S, A, B;
		cin >> S >> A >> B;
		set<char> check;

		int ok = 1;
		int det1 = 0, det2 = 0;
		for(int i = 0; i < S.size(); ++i) {
			int c = S[i] - 'a';
			int a = A[i] - 'a';
			int b = B[i] - 'a';

			if(ans[c] == -1) { // vc tem escolha
				if(!det1 and !det2 and a == b) { // vc nao tem escolha
					if(st.count(a) == 0) {
						ok = 0;
						break;
					} // se a nao tiver disponivel, nao tem como ne fio
					ans[c] = a;
					st.erase(a); // deixa a indisponivel
				} else {
					// vc finalmente tem escolha
					if(det1 and det2) { // tanto faz qual vc pega
						assert(st.size());
						ans[c] = *st.begin();
						st.erase(ans[c]);
					} else if(det1) {
						assert(st.size());
						ans[c] = *st.begin();
						st.erase(*st.begin());
					} else if(det2) {
						assert(st.size());
						ans[c] = *st.rbegin();
						st.erase(*st.rbegin());
					} else {
						auto it = st.upper_bound(a);
						if(it != st.end() and *it < b) {
							det1 = 1;
							det2 = 1;
							ans[c] = *it;
							st.erase(*it);
						} else {
							// pode seguir dois caminhos
							vector<int> anss = ans;
							set<int> stt = st;

							int det = 0;
							int flag = 1;
							// escolhe primeiro caminho, pra direita
							if(st.count(b)) {
								ans[c] = b;
								st.erase(b);
								for(int j = i+1; j < S.size(); ++j) {
									int c, b;
									c = S[j] - 'a';
									b = B[j] - 'a';
									if(ans[c] >= 0) {
										if(!det and ans[c] > b) flag = 0;
									} else {
										assert(st.size());
										ans[c] = *st.begin();
										st.erase(*st.begin());
									}
									det = det or ans[c] < b;
								}
							} else flag = 0;

							if(flag) break;

							ans = anss;
							st = stt;

							det = 0;
							flag = 1;
							if(st.count(a)) {
								st.erase(a);
								ans[c] = a;
								for(int j = i+1; j < S.size(); ++j) {
									int c, a;
									c = S[j] - 'a';
									a = A[j] - 'a';
									if(ans[c] >= 0) {
										if(ans[c] < a and !det) flag = 0;
									} else {
										assert(st.size());
										ans[c] = *st.rbegin();
										st.erase(*st.rbegin());
									}
									det = det or ans[c] > a;
								}
							} else flag = 0;

							if(flag) break;

							ok = 0;
							break;
						}
					}
				}
			}

			if(ans[c] > b and !det2) {
				ok = 0;
				break;
			}
			if(ans[c] < a and !det1) {
				ok = 0;
				break;
			}
			if(ans[c] > a) det1 = 1;
			if(ans[c] < b) det2 = 1;
		}

		if(ok) {
			cout << "YES\n";
			for(int x : ans) {
				if(x == -1) {
					assert(st.size());
					x = *st.begin();
					st.erase(st.begin());
				}
				assert(x >= 0);
				if(check.count('a' + x)) assert(0);
				check.insert('a' + x);
				cout << char('a' + x);
			}
			cout << '\n';
		} else {
			cout << "NO\n";
		}
	}
}