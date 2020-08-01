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
#define DEBUG 1
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
const int NIL = -inf;
int popcount(int x) { return __builtin_popcount(x); }


int N;
vecpii timber;

ll solve() {
    ll ret = 0;
    map<ll, ll> M;
    sort(ALL(timber));
    ret = max(timber.begin()->second, timber.rbegin()->second);
    FORO(i, N) {
        ll P = timber[i].first;
        ll H = timber[i].second;
        // [, P] + [P + H]
        getMax(M[P + H], M[P] + H);
        // [, P - H] + [P - H, P]
        getMax(M[P], M[P - H] + H);
        getMax(ret, max(M[P], M[P + H]));
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    FORI(t, T) {
        cin >> N;
        timber.resize(N);
        FORO(i, N) cin >> timber[i].first >> timber[i].second;
        cout << "Case #" << t << ": ";
        cout << solve() << endl;
    }

    return 0;
}