#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 100007;
const int M = 1e9 + 7;

int f[2][N];
int acc[N];

int a[N];

int main() {
    int n, k;
    cin >> n >> k;

    for(int i = 0; i < n; ++i) cin >> a[i];
    // pra 0
    f[0][0] = 1;
    for(int j = 0; j <= k; j++) {
        acc[j] = 1;
    }

    int cur = 1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= k; ++j) {
            f[cur][j] = acc[j];
            if(j - a[i] > 0) f[cur][j] = (f[cur][j] - acc[j - a[i] - 1] + M)%M;
        }

        acc[0] = f[cur][0];
        for(int j = 1; j <= k; ++j) {
            acc[j] = (f[cur][j] + acc[j-1])%M;
        }
        cur = 1 - cur;
    }

    cout << f[1-cur][k] << endl;
}
