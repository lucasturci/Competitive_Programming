#include <bits/stdc++.h>
using namespace std;

const int maxn = 2020;
const double eps = 1e-8;
int n, a, b, opt[maxn][maxn];
double dp[maxn][maxn], pa[maxn], pb[maxn], pab[maxn];

int solve(double mid){
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= a; j++){
            double &d = dp[i][j];
            int &o = opt[i][j];

            d = dp[i - 1][j];
            o = 0;

            if(j && d < dp[i - 1][j - 1] + pa[i]){
                d = dp[i - 1][j - 1] + pa[i];
                o = 1;
            }

            if(d < dp[i - 1][j] + pb[i] - mid){
                d = dp[i - 1][j] + pb[i] - mid;
                o = 2;
            }

            if(j && d < dp[i - 1][j - 1] + pab[i] - mid){
                d = dp[i - 1][j - 1] + pab[i] - mid;
                o = 3;
            }
        }
    }

    int ret = 0, la = a;

    for(int i = n; i >= 1; i--){
        if(opt[i][la] > 1)
            ret++;

        if(opt[i][la] & 1)
            la--;
    }

    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);

    cin >> n >> a >> b;

    for(int i = 1; i <= n; i++)
        cin >> pa[i];

    for(int i = 1; i <= n; i++)
        cin >> pb[i];

    for(int i = 1; i <= n; i++)
        pab[i] = pa[i] + pb[i] - pa[i] * pb[i];

    double lo = 0, hi = 1, mid;

    for(int it = 0; it < 50; it++){
        mid = (lo + hi) / 2;

        if(solve(mid) > b)
            lo = mid;
        else
            hi = mid;
    }

    int ans = solve(hi);

    cout << fixed << setprecision(10) << dp[n][a] + hi * b << endl;

    return 0;
}