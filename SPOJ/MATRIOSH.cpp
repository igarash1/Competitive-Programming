#include <cstdio>
#include <cstring>
#include <stack>
#include <cctype>
#include <algorithm>

using namespace std;
const int MAXN = 1000000;

stack<int> stk;
char s[20 * MAXN];
int A[MAXN];
int right[MAXN];
int ok;

int search(int l, int r) {
  int t = 0, s = 0;
  for (int i = l + 1; i < r; i = right[i] + 1) {
    t = max(t, search(i, right[i]));
    s += -A[i];
  }
  if (max(s, t) >= A[r]) ok = 0;
  return A[r];
}

int main() {
  while (gets(s) != NULL) {

    stk = stack<int>();
    int l = strlen(s);
    int i = 0, n = 0;

    for (; s[i] != '-' && !isdigit(s[i]) && i < l; i++);

    ok = 1;
    for (; ok && i < l; n++) {

      int v = 0, op = 1;
      for (; (s[i] == '-' || isdigit(s[i])) && i < l; i++) {
        if (s[i] == '-') op = -1;
        else v = v * 10 + (s[i] - '0');
      }

      v *= op;
      A[n] = v;

      if (v < 0) {
        stk.push(n);
      } else {
        if (stk.empty()) ok = 0;
        else if (v == -A[stk.top()]) right[stk.top()] = n, stk.pop();
        else stk.push(n);
      }

      for (; s[i] != '-' && !isdigit(s[i]) && i < l; i++);
    }

    if (n == 0) continue;

    if (!stk.empty()) ok = 0;
    for (int i = 0; ok && i < n; i = right[i] + 1)
      search(i, right[i]);

    puts(ok ? ":-) Matrioshka!" : ":-( Try again.");
  }
  return 0;
}
