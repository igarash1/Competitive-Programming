// TLE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define CLR(x) memset(x,0,sizeof x)

typedef struct Pair {
  int first, second;
} pii;

inline int cmp(const pii& a,const pii& b) {
  return a.first < b.first;
}

int neg;
inline void ifast(int *x) {
    register int c = getchar_unlocked();
    *x = 0;
    neg = 0;
    for(; ((c < 48||c > 57) && c != '-'); c = getchar_unlocked());
    if(c=='-') {
        neg = 1;
        c = getchar_unlocked();
    }
    for(;c > 47 && c < 58; c = getchar_unlocked()) {
      *x = ((*x)<<1) + ((*x)<<3) + c - 48;
    }
    if(neg) *x = -*x;
}

#define mx 30000 * 15010
#define mxn 15010

int n, k;
int pref[mxn];

int BN;
unsigned long long btsx[mxn/64+1];
unsigned long long dat[mxn][mxn/64+1];
pii sidx[mxn], sidx2[mxn];
int bidx[mxn], bidx2[mxn];
int ibn;
int mk;
int curk;
int i, j;

inline void add(int i) {
  while(i <= BN) {
    for(j = 0;j <= curk;j++) dat[i][j] |= btsx[j];
    i += i & - i;
  }
}

inline void sum(int i) {
  CLR(btsx);
  while(i > 0) {
    for(j = 0;j <= curk;j++) btsx[j] |= dat[i][j];
    i -= i & - i;
  }
}

inline int ok(int targ) {  
  int i;
  for(i = 1;i <= n;i++) {
    sidx2[i].first = pref[i] - targ;
    sidx2[i].second = i;
  }

  std::sort(sidx2+1,sidx2+1+n,cmp);

  ibn = 1;
  for(i = 1;i <= n;i++) {
    while(ibn < BN-1 && sidx2[i].first > sidx[ibn].first) ibn++;
    bidx2[sidx2[i].second] = BN - ibn;
  }
  curk = 0;

  for(i = 1;i <= BN;i++) CLR(dat[i]);
  for(i = 1;i <= n;i++) {
    sum(bidx2[i]);
    
    for(j = mk;j >= 0;j--) {
      btsx[j] <<= 1;
      if(j > 0) btsx[j] |= (btsx[j-1]>>63)&1;
    }
    
    if(sidx[i].first <= targ) btsx[0] |= 1;
    
    add(bidx[i]);
    if(i % 64 == 0) curk++;
  }

  return (btsx[(k-1)/64]>>((k-1)%64))&1;
}

int main() {
  int ntest;
  int a;
  int lo, mid, hi;
  int MX;
  int itest, i;

  ifast(&ntest);

  for(itest = 0;itest < ntest;itest++) {

    ifast(&n); ifast(&k);

    MX = 0;
    for(i = 0;i < n;i++) {
      ifast(&a);
      pref[i+1] = pref[i] + a;
      if(a > 0) MX += a;
      else MX += -a;
    }

    for(i = 1;i <= n;i++) {
      sidx[i].first = pref[i];
      sidx[i].second = i;
    }

    std::sort(sidx+1,sidx+1+n,cmp);

    BN = 0;
    for(i = 1;i <= n;i++) {
      if(i == 1 || sidx[i-1].first != sidx[i].first) BN++;
    }
    BN++;
    
    ibn = 0;
    for(i = 1;i <= n;i++) {
      if(i == 1 || sidx[i-1].first != sidx[i].first) ibn++;
      bidx[sidx[i].second] = BN - ibn;
    }
    mk = k/64;
    
    lo = -mx, hi = mx;
    while(lo+1 < hi) {
      mid = (lo + hi)/2;
      if(ok(mid)) {
	hi = mid;
      }else {
	lo = mid;
      }
    }
    
    printf("%d\n",hi);
  }

  return 0;
}
