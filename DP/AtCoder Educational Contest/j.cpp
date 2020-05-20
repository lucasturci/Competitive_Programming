#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 100007;

bool f[N];
int a[1007];
int main() {
    int n, k; cin >> n >> k;

    for(int i = 0; i < n; ++i) cin >> a[i];

    for(int i = 1; i <= k; ++i) {
        for(int j = 0; j < n; ++j) {
            if(i - a[j] >= 0) f[i] = f[i] or (!f[i - a[j]]);
        }
    }

    cout << (f[k]? "First" : "Second") << endl;
}
