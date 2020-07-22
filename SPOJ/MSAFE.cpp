#include <cstdio>
#include <algorithm>

using namespace std;
#define FORO(i, n) for(int i = 0;i < n;i++)
#define MAX 10000000LL
typedef long long ll;
ll s[100000];
ll P[100000];

int main() {
  ll n;
  scanf("%lld", &n);
  FORO(i, n) {
    scanf("%lld", P + i);
  }

  sort(P, P + n);
  FORO(i, n) {
    if (i) s[i] = s[i - 1];
    s[i] += P[i];
  }

  ll ans = 1000000000000LL;
  for (ll ix = 0; ix < n; ix++) {

    ll p = P[ix] + MAX / 2LL;
    p %= MAX;
    if (!p) p = MAX;

    ll jx = lower_bound(P, P + n, p) - P;
    // printf("ix = %lld,jx = %lld, p = %lld\n",ix,jx,p);

    ll candans = 0;

    if (ix >= jx) {
      candans = (P[ix] * (ix - jx + 1) - (jx ? s[ix - 1] - s[jx - 1] : s[ix - 1]));
      candans += (MAX - P[ix]) * (jx) + (jx ? s[jx - 1] : 0);
      candans += (s[n - 1] - s[ix]) - (n - ix) * P[ix];
    } else {
      candans = ix * P[ix] - s[ix] + P[ix];
      candans += MAX * (n - jx) - (s[n - 1] - s[jx - 1]) + (n - jx) * P[ix];
      candans += (s[jx - 1] - s[ix]) - (jx - ix - 1) * P[ix];
    }
    ans = min(ans, candans);
  }

  printf("%lld\n", ans);

  return 0;
}


