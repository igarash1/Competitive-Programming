#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int MAXN = 1 << 16;
const unsigned ALLONE = 0xffffffff;
unsigned ans;

int n;
unsigned A[MAXN];
unsigned dat[2 * MAXN];

void init(int n_) {
  for (n = 1; n < n_; n <<= 1);
  memset(dat, 0xff, sizeof dat);
}

void update(int i, unsigned x) {
  i += n - 1;
  dat[i] = x;
  for (i >>= 1; i > 0; i >>= 1) {
    dat[i] = dat[i * 2] & dat[i * 2 + 1];
  }
}

void query(int a, int b, int l = 1, int r = -1, int k = 1) {
  if (r < 0) r = n + 1;
  if (r <= a || b <= l) return;
  else if (a <= l && r <= b) {
    ans &= dat[k];
  } else {
    query(a, b, l, (l + r) / 2, k * 2);
    query(a, b, (l + r) / 2, r, k * 2 + 1);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, k;
    scanf("%d %d", &n, &k);
    init(3 * n);
    for (int i = 1; i <= n; i++) {
      scanf("%u", &A[i]);
    }
    for (int i = 1; i <= n; i++) {
      update(i, A[i]);
      update(i + n, A[i]);
      update(i + n + n, A[i]);
    }
    for (int i = n + 1; i <= 2 * n; i++) {
      ans = ALLONE;
      query(max(i - k, 1), min(i + k + 1, 3 * n + 1));
      printf("%u", ans);
      if (i == 2 * n) puts("");
      else putchar(' ');
    }
  }
  return 0;
}  

