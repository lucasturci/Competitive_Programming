// https://csacademy.com/contest/archive/task/strings/statement/

#include <bits/stdc++.h>

#define pb push_back

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;

const ll M = 1e9 + 7;
const ll X = 31;

struct node {
    char val;
    int prior, cnt;
    char lazy; // reverte ou nao
    ll h1, h2; // hash em ordem e hash revertido
    node * l, * r;

    node(){
        cnt = 1;
        prior = rng();
        l = r = NULL;
        h1 = h2 = 0;
        lazy = 0;
    }
    node(char c): node() {
        val = c;
        h1 = h2 = c - 'a' + 1;
    }
};
typedef node * treap;

ll pot[400007];

void prop(treap t) {
    if(t and t->lazy) {
        swap(t->l, t->r);
        swap(t->h1, t->h2);

        if(t->l) t->l->lazy = 1 - t->l->lazy;
        if(t->r) t->r->lazy = 1 - t->r->lazy;

        t->lazy = 0;
    }
}

void upd(treap t) {
    // IMPORTANTE: NO UPDATE, TEM QUE PROPAGAR OS FILHOS ANTES DE USAR O VALOR DELES
    prop(t->l);
    prop(t->r);

    int cntl = (t->l? t->l->cnt : 0);
    int cntr = (t->r? t->r->cnt : 0);

    
    t->cnt = 1 + cntl + cntr;
    t->h1 = (((t->l? t->l->h1 : 0) * pot[cntr + 1] % M) + ((t->val - 'a' + 1) * pot[cntr] % M) + (t->r? t->r->h1 : 0)) % M;
    t->h2 = (((t->r? t->r->h2 : 0) * pot[cntl + 1] % M) + ((t->val - 'a' + 1) * pot[cntl] % M) + (t->l? t->l->h2 : 0)) % M;
}



// retorna o valor na posicao p (0-based) como o mais esquerda de r - ou seja, l vai ter caras na sua arvore
void split_pos(treap t, treap & l, treap & r, int p, int s = 0) {
    if(t == 0) return void(l = r = 0);

    prop(t);

    int left = s + (t->l? t->l->cnt : 0);
    if(left >= p) {
        r = t;
        split_pos(t->l, l, t->l, p, s);
    } else {
        l = t;
        split_pos(t->r, t->r, r, p, left + 1);
    }

    upd(t);
}

void merge(treap & t, treap l, treap r) {

    prop(l);
    prop(r);
    if(l == 0 or r == 0) t = l? l : r;
    else if(l->prior > r->prior) {
        t = l;
        merge(t->r, t->r, r);
    } else {
        t = r;
        merge(t->l, l, t->l);
    }

    upd(t);
}

char at(treap t, int p, int s = 0) {
    if(t == 0) throw runtime_error("Out of bounds at position " + to_string(p));
    prop(t);
    int left = s + (t->l? t->l->cnt : 0);

    if(left == p) return t->val;
    else if(left > p) return at(t->l, p, s);
    else return at(t->r, p, left + 1);
}


void push_back(treap & t, char c) {
    treap n = new node(c);
    merge(t, t, n);
}

bool query(treap & t, int l, int r) {
    treap t1, t2, t3;

    split_pos(t, t1, t2, l);
    split_pos(t2, t2, t3, r - l + 1);
    assert(t2);
    bool ans = t2->h1 == t2->h2;

    merge(t, t1, t2);
    merge(t, t, t3);

    return ans;
}

void update(treap & t, int l, int r) {
    treap t1, t2, t3;

    split_pos(t, t1, t2, l);
    split_pos(t2, t2, t3, r - l + 1);
    assert(t2);

    assert(t2->lazy == 0);
    t2->lazy = 1;
    merge(t, t1, t2);
    merge(t, t, t3);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    pot[0] = 1;
    for(int i = 1; i < 400007; i++) {
        pot[i] = pot[i-1] * X % M;
    }

    int n, q; cin >> n >> q;

    string s; cin >> s;

    treap t = NULL;
    for(char c : s) push_back(t, c);

    for(int i = 0; i < q; ++i) {
        char op; cin >> op;

        if(op == 'Q') { // se eh palindromo
            int l, r; cin >> l >> r;
            l--, r--;

            cout << (query(t, l, r)? "YES" : "NO") << '\n';
        } else if(op == 'M') {
            int op2; cin >> op2;

            if(op2 == 1) {
                int i, j, k; cin >> i >> j >> k;
                i--, j--;

                treap t1, t2, t3;
                split_pos(t, t1, t2, i);
                split_pos(t2, t2, t3, j - i + 1);

                merge(t, t1, t3);

                split_pos(t, t1, t3, k);
                merge(t1, t1, t2);
                merge(t, t1, t3);

            } else if(op2 == 2) {
                int i, j; cin >> i >> j;
                i--, j--;
                update(t, i, j);
            } else {
                int i; char c;
                cin >> i >> c;
                i--;
                treap r;
                split_pos(t, t, r, i);
                treap n = new node(c);
                merge(t, t, n);
                merge(t, t, r);
            }
        }
    }
}
