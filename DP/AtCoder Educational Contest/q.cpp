#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define pb push_back

const int N = 3007;
const int M = 1e9 + 7;

int f[N][N];
int n; 
string s; 

int pre[N], suf[N];

int main() {
    cin >> n;
    cin >> s;
    s += '<';

    f[0][1] = 1;
    pre[1] = 1;
    suf[1] = 1;

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= i+1; ++j) {
            int men = i < n and s[n - i - 1] == '>';
            if(men) {
                f[i][j] = pre[j-1];
            } else {
                f[i][j] = j <= i? suf[j] : 0;
            }
        }

        memset(pre, 0, sizeof pre);
        memset(suf, 0, sizeof suf);

        pre[1] = f[i][1];
        for(int j = 2; j <= i+1; ++j) {
            pre[j] = (pre[j-1] + f[i][j])%M;
        }

        suf[i+1] = f[i][i+1];
        for(int j = i; j >= 1; --j) {
            suf[j] = (suf[j+1] + f[i][j])%M;
        }
    }

    cout << f[n][1] << endl;
}
