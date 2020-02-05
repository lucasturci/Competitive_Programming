// I want to find the kth smallest number in the interval [l, r]
// https://www.spoj.com/problems/MKTHNUM/

/*
    To solve this problem, answer the queries offline and at the same time,
    Binary search the queries on the answer, and to know if the guess is too big or to small you just have to count how many 
    guys less than the guess there are on the interval of the query. To do that, you can go from the smallest to the largest guys
    and activate their positions. Once you are in the guess of a query, you just have to count how many active positions are in its interval

    At each iteration of the while loop you do that and calculate if the guesses of the queries are too big or small. Then update the new search space of each query
    Overall complexity is O(Q*log(N) * log(M)), M is the maximum element
    If M << N this is nice, if M >> N you can compress and make it equal to N
*/

#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 100007;

vector<int> pos[N];
int v[N];
int L[N], R[N], K[N], ans[N];
int Lo[N], Hi[N];
vector<int> qu[N];

// BIT part
int bit[N];
int query(int x) {
    int tot = 0;
    for(; x; x -= x&(-x)) {
        tot += bit[x];
    }
    return tot;
}
inline int query(int l, int r) {
    return query(r) - (l? query(l-1) : 0);
}
void update(int x) {
    for(; x < N; x += x&(-x)) {
        bit[x]++;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;

    vector<int> vec;
    
    for(int i = 1; i <= n; ++i) {
        cin >> v[i];
        vec.pb(v[i]);
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    int m = vec.size();

    for(int i = 1; i <= n; ++i) {
        int j = lower_bound(vec.begin(), vec.end(), v[i]) - vec.begin();
        pos[j].pb(i);
    }

    for(int i = 0; i < q; ++i) {
        cin >> L[i] >> R[i] >> K[i];
        Lo[i] = 0, Hi[i] = m-1;
        if(Lo[i] <= Hi[i])
            qu[(Lo[i] + Hi[i])>>1].pb(i);
    }

    while(1) {
        for(int i = 0; i < m; ++i) {  
            // activate the positions
            for(int x : pos[i]) update(x);

            // update the search space of the queries
            for(int p : qu[i]) {
                if(query(L[p], R[p]) >= K[p]) {
                    ans[p] = i;
                    Hi[p] = i-1;
                } else {
                    Lo[p] = i+1;
                }
            }

            qu[i].clear();
        }

        // calculate new mids of the queries
        int flag = 0;
        for(int i = 0; i < q; ++i) {
            if(Lo[i] <= Hi[i]) {
                qu[(Lo[i] + Hi[i]) >> 1].pb(i);
                flag = 1;
            }
        }
        memset(bit, 0, sizeof bit);

        if(flag == 0) break;
    }

    for(int i = 0; i < q; ++i) cout << vec[ans[i]] << '\n';
}