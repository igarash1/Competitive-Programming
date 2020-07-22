#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;
#define A first
#define B second
#define FORI(i, n) for(int i = 1;i <= n;i++)
#define FORO(i, n) for(int i = 0;i < n;i++)

int min(int a, int b, int c) {
  return min(a, min(b, c));
}

int dp[100001];
int id[100001];
int f[100001];
int sf[100001];
pii S[100001];

int main() {
  int n;
  scanf("%d", &n);
  FORI(i, n) {
    scanf("%d", f + i);
    sf[i] = sf[i - 1] + f[i];
  }

  int m;
  scanf("%d", &m);
  FORO(i, m) {
    scanf("%d %d", &S[i].A, &S[i].B);
    if (i) {
      for (int j = S[i - 1].A; j < S[i].A; j++) id[j] = i - 1;
    }
  }

  for (int j = S[m - 1].A; j <= n; j++) id[j] = m - 1;

  sort(S, S + m);
  int ans = 0;
  FORO(i, m) {
    int limit = min((i + 1 == m ? n + 1 : S[i + 1].A), n + 1, S[i].A + S[i].B);
    int j = (S[i].A - S[i].B < 0 ? -(S[i].A - S[i].B) + S[i].A : S[i].A);
    for (; j < limit; j++) {
      if (i == 0 || id[j - S[i].B] == i - 1) {
        dp[j] = sf[j] - sf[j - S[i].B] + dp[j - S[i].B];
      }
      if (id[j - 1] == i) dp[j] = max(dp[j], dp[j - 1]);
      ans = max(ans, dp[j]);
    }
    if (i + 1 < m)
      for (; j < S[i + 1].A; j++) dp[j] = max(dp[j], dp[j - 1]);
  }

  printf("%d\n", ans);
  return 0;
}

