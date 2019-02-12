// O(n log n log c)
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
void chmin(int &a,int &b) { if(a > b) a = b; }
void chmax(int &a,int &b) { if(a < b) a = b; }
#define A first
#define B second
const int MAXN = 15010;
const int MAX = 30010;

int n, k;
int A[MAXN];
int pref[MAXN];
int pref2[MAXN], idx[MAXN];
pii dat[MAXN];

inline void init() {
    for(int i = 0;i <= n;i++) dat[i].A = n, dat[i].B = 0;
}
inline void update(pii &a, pii b) { chmin(a.A, b.A); chmax(a.B, b.B); }
inline void insertVal(int i, pii v) {
    for(;i <= n;i += i & - i) update(dat[i], v);
}
inline pii getVal(int i) {
    pii ret(MAXN, 0);
    for(;i > 0;i -= i & -i) update(ret, dat[i]);
    return ret;
}

bool OK(int M) {
    init();
    pii res;
    for(int i = 1;i < n - 1;i++) {
        int k = n - (lower_bound(pref2, pref2 + n, pref[i] - M) - pref2);
        res = getVal(k);
        if(pref[i] <= M) insertVal(idx[i], pii(1, 1));
        if(res.A < n && res.B > 0) {
            res.A++; res.B++;
            insertVal(idx[i], res);
        }
    }
    return res.A <= k && k <= res.B;
}

int solve(int L, int R) {
    while(R - L > 1) {
        int M = (L + R) / 2;
        if(OK(M)) R = M;
        else L = M;
    }
    return R;
}

int main() {
    ios::sync_with_stdio(false);
    int tcase; cin >> tcase;
    while(tcase--) {
        cin >> n >> k;
        
        int L = -1, R = 1;
        pref[0] = pref2[0] = 0;
        for(int i = 1;i <= n;i++) {
            int a; cin >> a;
            pref2[i] = (pref[i] = pref[i - 1] + a);
            if(a > 0) R += a; else L += a;
        }
        pref2[n + 1] = pref[n + 1] = L;
        n+=2;
        sort(pref2, pref2 + n);
        for(int i = 1;i < n - 1;i++) {
            idx[i] = n - (lower_bound(pref2, pref2 + n, pref[i]) - pref2);
        }

        cout << solve(L, R) << endl;
    }

    return 0;
}
