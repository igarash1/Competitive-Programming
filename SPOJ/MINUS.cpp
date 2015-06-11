#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int B = 10000;
const int N = 100;

int a[N];
int dp[N][2*B];
int pre[N][2*B];

void solve(int n,int m) {

  memset(dp,0,sizeof dp);
  dp[0][B+a[0]] = 1;
  pre[0][B+a[0]] = -1;
  for(int i = 1;i < n;i++) {
    for(int j = 0;j < 2*B;j++) {
      if(a[i]+j < 2*B && dp[i-1][j+a[i]]) {
				dp[i][j] = 1;
				pre[i][j] = 1; // -
      }
      if(i > 1 && j >= a[i] && dp[i-1][j-a[i]]) {
				dp[i][j] = 1;
				pre[i][j] = 2; // +
      }
    }
  }

  vector<int> op;
  for(int i = n-1, j = m+B;i > 0;i--) {
    op.push_back(pre[i][j]);
    j = pre[i][j] == 1 ? j+a[i] : j-a[i];
  }
  reverse(op.begin(),op.end());
  
  int cur = 0, last = -1;
  for(int i = 0;i < op.size();i++) {
    if(op[i] == 1) cur++;
    else if(op[i] == 2) printf("%d\n",cur+1);
  }
  while(cur--) puts("1");
}

int main() {
  int t;
  scanf("%d",&t);
  while(t--) {
    int n, m;
    scanf("%d %d",&n,&m);
    for(int i = 0;i < n;i++) scanf("%d",a+i);
    solve(n,m);
    puts("");
  }
  return 0;
}

