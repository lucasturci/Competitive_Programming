#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 3007;

int n;

double memo[307][307][307];
bool vis[307][307][307];

double solve(int ones, int twos, int tres) {
    if(ones + twos + tres == 0) return 0;

    double & st = memo[ones][twos][tres];
    if(!vis[ones][twos][tres]) {
        vis[ones][twos][tres] = true;

        st = 1;
        if(ones) st += double(ones)/double(n) * solve(ones-1, twos, tres);
        if(twos) st += double(twos)/double(n) * solve(ones+1, twos-1, tres);
        if(tres) st += double(tres)/double(n) * solve(ones, twos+1, tres-1);
        st = st * double(n);
        st /= (ones + twos + tres);
    }
    return st;
}
int main() {
    int cnt[4] = {0};
    cin >> n;

    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        cnt[a] ++;
    }

    cout << fixed << setprecision(10) << solve(cnt[1], cnt[2], cnt[3]) << endl;
}
