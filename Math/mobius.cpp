#include <bits/stdc++.h>

using namespace std;

const int N = 100007;
int mu[N];
void mobius() {
    memset(mu, 0, sizeof mu);
    mu[1] = 1;
    for(int i = 1; i < N; ++i) {
        for(int j = i + i; j < N; j += i) {
            mu[j] -= mu[i];
        }
    }
}

int main() {
    mobius();
}