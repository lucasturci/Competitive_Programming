#include <bits/stdc++.h>

using namespace std;

const int N = 100007;
int phi[N];
void euler() {
    for(int i = 1; i < N; ++i) {
        phi[i] = i;
    }
    for(int i = 1; i < N; ++i) {
        for(int j = i + i; j < N; j += i) {
            phi[j] -= phi[i];
        }
    }
}

int main() {
    euler();
}