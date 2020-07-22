#include <cstdio>
#include <cstring>
#include <map>

using namespace std;
typedef unsigned long long S;

map<S, int> dp;

int getith(S &s, int i) {
  return (0xF & (s >> (4ULL * i)));
}

int rec(S s) {
  if (dp[s]) return dp[s];
  int l = 0;
  for (int i = 1; i < 10; i++)
    l += !!getith(s, i);
  if (l + 1 == getith(s, 0)) {
    return dp[s] = (getith(s, 1) > 1 ? 1 : -1);
  } else {
    S ns = 0;
    for (int i = 0; i < 10; i++) {
      int x = getith(s, i);
      if (x) ns |= ((x - 1ULL) << (4ULL * i));
    }
    return dp[s] = rec(ns);
  }
}

int main() {
  dp[0] = 1;
  dp[1] = -1;
  for (int i = 1; i <= 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i == j + 1) continue;
      S s = i;
      for (int k = 0; k < j; k++) s |= (1ULL << (4ULL * (k + 1)));
      dp[s] = 1;
    }
  }

  int a[10];
  int t;
  scanf("%d", &t);
  while (t--) {
    for (int i = 0; i < 10; i++) scanf("%d", &a[i]);
    S s = 0;
    for (int i = 0; i < 10; i++)
      s |= S(a[i]) << (4ULL * i);
    puts(rec(s) > 0 ? "W" : "L");
  }
  return 0;
}

