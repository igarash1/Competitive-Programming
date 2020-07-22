#include <stdio.h>
#include <algorithm>

using namespace std;
const long long M = 1000000003;

long long dp[1001][1001][2];

int main() {
  int N, K;
  scanf("%d %d", &N, &K);
  N -= 2;

  dp[1][0][0] = dp[1][1][1] = 1;
  for (int i = 2; i <= N; i++) {
    for (int j = 0; j <= min(N + 1, 2 * K) / 2; j++) {
      dp[i][j][0] = dp[i - 1][j][0] + dp[i - 1][j][1];
      if (j > 0) dp[i][j][1] = dp[i - 1][j - 1][0];
      dp[i][j][0] %= M;
      dp[i][j][1] %= M;
    }
  }

  printf("%d\n", (int) ((dp[N][K][0] + dp[N][K][1] + dp[N][K - 1][0] + dp[N][K - 1][0]) % M));
  return 0;
}


