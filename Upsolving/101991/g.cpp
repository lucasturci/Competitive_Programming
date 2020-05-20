#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL_PC
  #define debug(args...) { cout.flush(); fflush(stdout); fprintf(stderr, args); }
#else
  #define debug(args...) ; /*  */
#endif
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second
using ll = long long;
using pii = pair<int, int>;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class Ty> Ty rnd(Ty a, Ty b) { return uniform_int_distribution<Ty>(a, b)(rng); }

template<class num> inline void rd(num &x) {
  char c; while(isspace(c = getchar()));
  bool neg = false;
  if(!isdigit(c)) neg = (c == '-'), x = 0;
  else x = c - '0';
  while(isdigit(c = getchar()))
    x = (x << 3) + (x << 1) + c - '0';
  if (neg) x = -x;
} template <class T, class... Args> inline void rd(T& x, Args&... args) { rd(x); rd(args...); }


#define div divv
const int NN = 1e6 + 7;
const int N = 1e5 + 5, INF = 0x3f3f3f3f;

int a[N];

struct SegTree {
  int n;
  int seg[4 * N];

  void build(int p, int i, int j) {
    if (i == j) seg[p] = a[i];
    else {
      int m = (i + j) / 2;
      build(p+p, i, m);
      build(p+p+1, m+1, j);
      seg[p] = __gcd(seg[p+p], seg[p+p+1]);
    }
  }

  void init(int n) {
    this->n = n;
    build(1, 0, n-1);
  }

  int query(int p, int i, int j, int l, int r) {
    if (i >= l && j <= r) return seg[p];
    else if (i > r or j < l) return 0;
    else {
      int m = (i + j) / 2;
      int L = query(p+p, i, m, l, r);
      int R = query(p+p+1, m+1, j, l, r);
      return __gcd(L, R);
    }
  }

  inline int query(int l, int r) {
    return query(1, 0, n-1, l, r);
  }
} st;

struct Query {
  int l, r, d, j;

  bool operator< (Query & q) const {
    return r < q.r;
  }
};

struct segtree {
  vector<int> seg;
  int n;

  segtree(){}
  segtree(int n) {
    this->n = n;
    seg.assign(n + n, 0);
  }

  void update(int p, int val) {
    for(seg[p += n] = val; p > 0; p >>= 1) {
      seg[p >> 1] = seg[p] + seg[p^1];
    }
  }

  ll query(int l, int r) {
    ll ans = 0;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l&1) ans += seg[l++];
      if(r&1) ans += seg[--r];
    }
    return ans;
  }
};


ll ans[N];
vector<pair<int, pii>> mp[NN];
vector<pii> Rs[NN], Ls[NN];
vector<int> div[NN];
segtree seg[NN];
segtree desativados[NN];
int posl[NN], posr[NN];

inline void _solve_(int __ntest__) {
  int n, q; rd(n, q);
  for (int i = 0; i < n; i++) rd(a[i]);
  st.init(n);
  
  vector<Query> qry(q);
  int tt = 0;
  vector<int> D;
  for (Query& i : qry) {
    rd(i.l, i.r, i.d);
    i.j = tt++;
    i.l--, i.r--;
    D.pb(i.d);
  }

  sort(D.begin(), D.end());
  D.erase(unique(D.begin(), D.end()), D.end());

  for(int d : D) mp[d].clear();

  auto getfi = [&](int i, int d) {
    int lo = i, hi = n-1, mi, ans = i;
    while(lo <= hi) {
      mi = (lo + hi) / 2;

      int cur = st.query(i, mi);
      if (cur == d) ans = mi, hi = mi-1;
      else if (__gcd(cur, d) == d) lo = mi+1;
      else hi = mi-1;
    }

    for (int j = max(i, ans-2); j <= min(n-1, ans+2); j++) {
      if (st.query(i, j) == d) return j;
    }
    return -1;
  };

  auto getse = [&](int i, int d) {
    int lo = i, hi = n-1, mi, ans = i;
    while(lo <= hi) {
      mi = (lo + hi + 1) / 2;
      int cur = st.query(i, mi);
      if (cur == d) ans = mi, lo = mi+1;
      else if (__gcd(cur, d) == d) lo = mi+1;
      else hi = mi-1;
    }

    for (int j = min(n-1, ans+2); j >= max(i, ans-2); j--) {
      if (st.query(i, j) == d) return j;
    }

    return -1;
  };

  for (int i = 0; i < n; i++) {
    for (int d : div[a[i]]) {
      if(find(D.begin(), D.end(), d) == D.end()) continue;
      pii cur = {getfi(i, d), getse(i, d)};
      if (cur.fi == -1 or cur.se == -1) continue;
      mp[d].eb(i, cur);
    }
  }

  for(int d : D) {
    seg[d] = segtree(mp[d].size());
    desativados[d] = segtree(mp[d].size());
    Rs[d].clear();
    Ls[d].clear();
  }

  for(int d : D) {
    for(int i = 0; i < mp[d].size(); ++i) {
      pii aux = mp[d][i].se;
      seg[d].update(i, aux.se - aux.fi + 1);
      Rs[d].eb(aux.se, i);
      Ls[d].eb(aux.fi, i);
    }
    sort(Rs[d].rbegin(), Rs[d].rend());
    sort(Ls[d].rbegin(), Ls[d].rend());

    posl[d] = posr[d] = 0;
  }

  sort(qry.rbegin(), qry.rend());

  for (Query& qr : qry) {
      int d = qr.d;
      int j = qr.j; // indice pra answer


      // substitui todas as posicoes que r > r da query por - l + 1
      while(posr[d] < Rs[d].size() and Rs[d][posr[d]].fi > qr.r) {
        seg[d].update(Rs[d][posr[d]].se, -mp[d][posr[d]].se.fi + 1);
        desativados[d].update(Rs[d][posr[d]].se, 1);
        posr[d]++;
      }

      while(posl[d] < Ls[d].size() and Ls[d][posl[d]].fi > qr.r) {
        seg[d].update(Ls[d][posl[d]].se, 0);
        desativados[d].update(Ls[d][posl[d]].se, 0);
        posl[d]++;
      }

      int l = lower_bound(mp[d].begin(), mp[d].end(), pair<int, pii>(qr.l, pii(0, 0))) - mp[d].begin();
      int r = lower_bound(mp[d].begin(), mp[d].end(), pair<int, pii>(qr.r, pii(0x3f3f3f3f, 0x3f3f3f3f))) - mp[d].begin();

      ans[j] = seg[d].query(l, r);
      ans[j] += (ll) qr.r * desativados[d].query(l, r);
  }

  for(int i = 0; i < qry.size(); ++i) printf("%lld\n", ans[i]);
}

int main() {
  freopen("gcdrng.in", "r", stdin);

  clock_t t = clock();
  for(int i = 1; i < NN; i++) {
    for(int j = i; j < NN; j += i) {
      t = t - t + t;
    }
  }

  printf("tempo = %lf\n", (clock() - t)/(1.0 * CLOCKS_PER_SEC));

  return 0;
  int ans = 0;
  int __T__; rd(__T__);
  for (int __i__ = 1; __i__ <= __T__; __i__++) _solve_(__i__);
  return 0;
}