#include <bits/stdc++.h>

#define pb push_back

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node {
    int val, prior;
    int cnt;
    node * l, * r;

    node(){
        cnt = 1;
        prior = rng();
        l = r = NULL;
    }
    node(int x): node() {
        val = x;
    }
};
typedef node * treap;

// Nessa funcao voce pode adicionar mais coisas, como a soma dos valores da subarvore, o maximo, etc.
void upd(treap t) {
    t->cnt = 1 + (t->l? t->l->cnt : 0) + (t->r? t->r->cnt : 0);
}

// menor que x vai pra esquerda, maior pra direita
void split(treap t, treap & l, treap & r, int x) {
    if(t == 0) return void(l = r = 0);
    if(t->val < x) {
        l = t;
        split(t->r, t->r, r, x);
    } else {
        r = t;
        split(t->l, l, t->l, x);
    }

    upd(t);
}

// retorna o valor na posicao p (0-based) como o mais esquerda de r - ou seja, l vai ter caras na sua arvore
void split_pos(treap t, treap & l, treap & r, int p, int s = 0) {
    if(t == 0) return void(l = r = 0);

    int left = s + (t->l? t->l->cnt : 0);
    if(left >= p) {
        r = t;
        split_pos(t->l, l, t->l, p, s);
    } else {
        l = t;
        split_pos(t->r, t->r, r, p, left + 1);
    }
}

void merge(treap & t, treap l, treap r) {
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

int at(treap t, int p, int s = 0) {
    if(t == 0) throw runtime_error("Out of bounds");
    int left = s + (t->l? t->l->cnt : 0);

    if(left == p) return t->val;
    else if(left > p) return at(t->l, p, s);
    else return at(t->r, p, left + 1);
}

void add(treap & t, int x) {
    treap n = new node(x);
    treap r = NULL;
    split(t, t, r, x);
    merge(t, t, n);
    merge(t, t, r);
}

void add(treap & t, int pos, int x) {
    treap n = new node(x);
    treap r = NULL;
    split_pos(t, t, r, pos);
    merge(t, t, n);
    merge(t, t, r);
}


int main() {

    treap t = NULL;

    for(int i = 10; i >= 1; --i) {
        add(t, i);
    }

    for(int i = 0; i < 10; ++i) cout << at(t, i) << ' ';
    cout << endl;

    add(t, 3, 18);

    for(int i = 0; i < 10; ++i) cout << at(t, i) << ' ';
    cout << endl;

}
