#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#ifdef DEBUG
const int R = 4;
#else
const int R = 320;
#endif
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef bitset<R> bs;

vector<vi> transpose(vector<vi> & mat) {
    int n = mat.size(), m = mat[0].size();

    vector<vi> ans(m, vi(n));
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            ans[i][j] = mat[j][i];
        }
    }
    return ans;
}

int gauss (vector < bs > a, int n, int m, bs & ans) {
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        for (int i=row; i<n; ++i)
            if (a[i][col]) {
                swap (a[i], a[row]);
                break;
            }
        if (! a[row][col])
            continue;
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row;
    }

    ans = bs();
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m];
    
    for (int i=0; i<n; ++i) {
        int sum = 0;
        for (int j=0; j<m; ++j)
            sum ^= ans[j] * a[i][j];
        if (sum != a[i][m])
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return 0x3f3f3f;
    return 1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n >> m;

    vector<vi> mat(n, vi(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            char c; cin >> c;
            mat[i][j] = c == 'B';
        }
    }
    
    bool changed = false;
    if(n < m) {
        swap(n, m);
        mat = transpose(mat);
        changed = true;
    }

    int moves[][2] = {{0, 0}, {-1, 0}, {0, -1}, {0, 1}};
    vector<bs> repr[3];
    
    repr[0].assign(m, bs());
    repr[1].assign(m, bs());
    repr[2].assign(m, bs()); // auxiliar

    int cur = 0;
    for(int i = 0; i < m; ++i) {
        repr[cur][i][i] = 1;
    }

    // fazer representacao das variaveis da ultima linha em funcao das variaveis da primeira linha
    for(int i = 0; i < n-1; ++i) {
        repr[2].assign(m, bs()); // auxiliar
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < 4; ++k) {
                int p = i + moves[k][0];
                int q = j + moves[k][1];
                if(q < 0 or q >= m or p < 0 or p >= n) continue;
                repr[2][j] ^= repr[cur ^ (i != p)][q]; 
            }

            if(mat[i][j]) repr[2][j].flip(m);
        }

        // cout << repr[cur][0] << ' ' << repr[cur][1] << endl;
        repr[1 - cur] = repr[2];
        cur = 1 - cur;
    }
    
    // cout << repr[cur][0] << ' ' << repr[cur][1] << endl;


    // criar equacoes das variaveis da ultima linha
    vector<bs> A(m, bs());

    for(int j = 0; j < m; ++j) {
        for(int k = 0; k < 4; ++k) {
            int p = n-1 + moves[k][0];
            int q = j + moves[k][1];
            if(q < 0 or q >= m or p < 0 or p >= n) continue;
            A[j] ^= repr[cur ^ (n-1 != p)][q];
            // cout << A[j] << endl;
        }
        // cout << endl;
        if(mat[n-1][j]) A[j].flip(m);
    }

    // cout << A[0] << endl;
    // cout << A[1] << endl;

    bs ans;
    if(gauss(A, m, m, ans) == 0) {
        cout << "IMPOSSIBLE\n";
    } else {
        // repete a representacao de todas as variaveis como variaveis da primeira linha
        repr[0].assign(m, bs());
        repr[1].assign(m, bs());
        

        cur = 0;
        for(int i = 0; i < m; ++i) {
            repr[cur][i][i] = 1;
        }

        vector<vi> output(n, vi(m));
        for(int i = 0; i < n; ++i) {
            repr[2].assign(m, bs()); // auxiliar
            for(int j = 0; j < m; ++j) {
                for(int k = 0; k < 4; ++k) {
                    int p = i + moves[k][0];
                    int q = j + moves[k][1];
                    if(q < 0 or q >= m or p < 0 or p >= n) continue;
                    repr[2][j] ^= repr[cur ^ (i != p)][q]; 
                }

                // cout << "i: " << i << ' ' << "j: " << j << " cur: " << cur << endl; 
                // cout << repr[cur][j] << endl;

                if(mat[i][j]) repr[2][j].flip(m);
                
                int tot = 0;
                
                for(int l = 0; l < m; ++l) {
                    if(repr[cur][j][l]) {
                        tot ^= ans[l];
                    }
                }
                if(repr[cur][j][m]) tot ^= 1;

                output[i][j] = tot;
                
                
            }
            repr[1 - cur] = repr[2];
            cur = 1 - cur;
            // cout << endl;
            
        }
        


        if(changed) output = transpose(output);

        for(vi & v : output) {
            for(int x : v) {
                cout << (x? 'P' : 'A') << ' ';
            }
            cout << '\n';
        }
    }
}