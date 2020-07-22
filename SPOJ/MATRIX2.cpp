#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN 1024
#define inf 110000000

int P[MAXN][MAXN];
int S[MAXN][MAXN];

int RCD[MAXN][MAXN];

int DB[MAXN][MAXN];
int AC[MAXN][MAXN];

int deq[MAXN];

int main() {
  int tc;
  scanf("%d", &tc);
  for (int tt = 0; tt < tc; tt++) {

    int A, B, C, D;
    int N, M;

    scanf("%d %d %d %d %d %d", &N, &M, &A, &B, &C, &D);
    for (int i = 1; i <= N; i++) {
      scanf("%d", &P[i][1]);
      for (int j = 2; j <= M; j++) P[i][j] = (P[i][j - 1] * 71 + 17) % 100 + 1;
    }

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + P[i][j];
        if (i >= C && j >= D)
          RCD[i][j] = S[i][j] - S[i - C][j] - S[i][j - D] + S[i - C][j - D];
        else
          RCD[i][j] = inf;
        DB[i][j] = AC[i][j] = inf;
      }
    }

    for (int i = 1; i <= N; i++) {
      int s = 0, t = 0;
      for (int j = 1; j <= M; j++) {
        while (s < t && RCD[i][deq[t - 1]] >= RCD[i][j]) t--;
        deq[t++] = j;
        if (j >= B - D - 1) {
          DB[i][j] = RCD[i][deq[s]];
          while (s < t && deq[s] <= j - (B - D - 1) + 1) s++;
        }
      }
    }

    for (int j = 1; j <= M; j++) {
      int s = 0, t = 0;
      for (int i = 1; i <= N; i++) {
        while (s < t && DB[deq[t - 1]][j] >= DB[i][j]) t--;
        deq[t++] = i;
        if (i >= A - 1 - C) {
          AC[i][j] = DB[deq[s]][j];
          while (s < t && deq[s] <= i - (A - C - 1) + 1) s++;
        }
      }
    }

    int ans = 0;
    for (int i = A; i <= N; i++)
      for (int j = B; j <= M; j++)
        ans = max(ans, S[i][j] - S[i - A][j] - S[i][j - B] + S[i - A][j - B] - AC[i - 1][j - 1]);
    printf("%d\n", ans);
  }
  return 0;
}


