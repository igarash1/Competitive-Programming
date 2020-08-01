//
// Created by Koki Igarashi on 7/27/20.
//

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef int Int;
typedef pair<Int, Int> pii;
typedef pair<Int, double> pid;
typedef pair<double, double> pdd;
typedef pair<Int, pii> pip;
typedef pair<pii, Int> ppi;
typedef pair<double, Int> pdp;
typedef vector<Int> veci;
typedef vector<double> vecd;
typedef vector<int> veci;
typedef vector<ll> vecll;
typedef vector<double> vecd;
typedef vector<pii> vecpii;
typedef vector<ppi> vecppi;
typedef vector<veci> mati;
typedef vector<vecll> matll;
typedef vector<vecd> matd;
#define PB(x) push_back(x)
#define EB(x) emplace_back(x)
#define ALL(x) x.begin(),x.end()
#define SZ(x) (x).size()
#define CLR(x) memset(x,0,sizeof x)
#define pdebug() printf("%d\n",__LINE__)
#define REP(i, a, b) for(int i = (a);i <= (b);i++)
#define FORO(i, n) REP(i,0,(int)n-1)
#define FORI(i, n) REP(i,1,(int)n)
#define FORIT(i, t) for(auto i = t.begin();i != t.end();i++)
#define eps 1e-6
#define sqr(x) ((x)*(x))
#define dist(_a, _b) sqrt(sqr(_a.A-_b.A)+sqr(_a.B-_b.B))
#define norm(_a) sqrt(sqr(_a.A)+sqr(_a.B))
#define DEBUG true
#if DEBUG
#define DUMP(a) do { std::cout << #a " = " << (a) << ", "; } while(false)
#define DUMPLN(a) do { std::cout << #a " = " << (a) << std::endl; } while(false)
#else
#define DUMP(a)
#define DUMPLN(a)
#endif
template<typename T, typename U>
inline void getMin(T &a, U b) { if (a > b) a = b; }
template<typename T, typename U>
inline void getMax(T &a, U b) { if (a < b) a = b; }
template<typename T>
vector<T> getVector(const int n) { return vector<T>(n); }
template<typename T>
vector<T> getVector(const int n, const T a) { return vector<T>(n, a); }
template<typename T>
vector<T> getEmptyVector() { return vector<T>(); }
template<typename T>
void appendAll(vector<T> &a, vector<T> b) { a.insert(a.end(), b.begin(), b.end()); }
// #define X first
// #define Y second
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const ll MOD = 1000000007;
const int MAXN = 1 << 17;
const int inf = 1 << 20;
const ll llinf = 1LL << 55LL;
const int NIL = -inf;
int popcount(int x) { return __builtin_popcount(x); }

class RMQ {
 public:
  const ll INIT = llinf;
  const ll INF = llinf;
  vector<ll> d;
  int n;

  RMQ(int n_) {
      for (n = 1; n < n_; n *= 2);
      d.resize(2 * n);
      for (int i = 0; i < 2 * n; i++) d[i] = INIT;
  }

  void update(int i, ll x) {
      i += n - 1;
      d[i] = min(d[i], x);
      for (i = (i - 1) >> 1; i > 0; i = (i - 1) >> 1) {
          d[i] = min(d[i * 2 + 1], d[i * 2 + 2]);
      }
  }

  ll query(int a, int b, int k = 0, int l = 0, int r = -1) {
      if (r == -1) r = n;

      if (b <= l || r <= a) return INF;
      if (a <= l && r <= b) return d[k];

      ll li = query(a, b, k * 2 + 1, l, (l + r) / 2);
      ll ri = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return min(li, ri);
  }
};

int N, M;
vecll C;

ll solve() {
    RMQ rmq(N);
    //DUMP(N); DUMPLN(M);
    rmq.update(0, 0);
    FORO(i, N) {
        if(C[i] == 0) continue;
        //DUMP(i - M); DUMPLN(i);
        ll cand = rmq.query(i - M, i);
        //DUMP(i); DUMPLN(cand);
        rmq.update(i, cand + C[i]);
    }
    ll ret = rmq.query(N - M - 1, N - 1);
    //DUMPLN(ret);
    return ret >= llinf ? -1 : ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    FORI(t, T) {
        cin >> N >> M;
        C.resize(N);
        FORO(i, N) cin >> C[i];

        cout << "Case #" << t << ": ";
        cout << solve() << endl;
    }

    return 0;
}