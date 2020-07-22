#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAXN = 104;

unsigned dp[MAXN][MAXN];
char str[MAXN][MAXN];

int get(int x, int i) {
  return (x >> i) & 1;
}

void set(int &x, int i) {
  x += 1 << i;
}

int main() {
  int M, N, K;
  scanf("%d %d %d", &M, &N, &K);
  for (int i = 1; i <= M; i++) {
    scanf("%s", &str[i][1]);
  }
  int s, k, ans = 0;
  for (int y = 1; y <= M; y++) {
    for (int x = 1; x <= N; x++) {
      for (int h = 1; h <= M - y + 1; h++) {
        for (int w = 1; w <= N - x + 1; w++) {
          s = dp[h - 1][w] | dp[h][w - 1];
          k = __builtin_popcount(s);
          if (!get(s, str[y + h - 1][x + w - 1] - 'A')) {
            k++;
            set(s, str[y + h - 1][x + w - 1] - 'A');
          }
          dp[h][w] = s;
          if (k == K) ans++;
          if (k > K) break;
        }
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
