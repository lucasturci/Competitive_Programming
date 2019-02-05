#include <bits/stdc++.h>
using namespace std;
const int N = 100007;
int phi[N];
void pi_function(string & s) {
	phi[0] = 0;
	for(int i = 1; i < s.size(); ++i) {
		int j = phi[i-1];
		while(j and s[i] != s[j]) j = phi[j - 1];

		phi[i] = s[i] == s[j]? j + 1 : 0;
	}
}

int main(){}