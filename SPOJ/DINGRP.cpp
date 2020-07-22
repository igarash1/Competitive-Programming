#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int inf = 100000000;

void getmin(int &a, int b) { if (a > b) a = b; }

/*
  dp[i][j][k] = 列[i...j]の先頭にk個のcolor[i]とおなじcompetitorを入れたときの最小のsend数
  dp[i][j][k] = min dp[i+1][u-1][0]+dp[u][j][k+1] (for all i that color[u] == color[i])
 */

int n, k;
int dp[100][100][6];
char color[103];

int rec(int l, int r, int x) {
  if (r < l) return 0;
  if (l == r && x == k - 1) return 1;
  if (dp[l][r][x] != -1) return dp[l][r][x];
  dp[l][r][x] = inf;
  if (x == k - 1) dp[l][r][x] = rec(l + 1, r, 0) + 1;
  for (int i = l + 1; i <= r; i++) {
    if (color[i] == color[l])
      getmin(dp[l][r][x], rec(l + 1, i - 1, 0) + rec(i, r, min(k - 1, x + 1)));
  }
  return dp[l][r][x];
}

int main() {
  scanf("%d %d", &n, &k);
  scanf("%s", color);
  memset(dp, -1, sizeof dp);
  int ans = rec(0, n - 1, 0);
  if (ans >= inf) ans = -1;
  printf("%d\n", ans);
  return 0;
}
