#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
const int MAXN = 100000;
const int inf = 1000000004;

struct xyp {
  int x, y;

  bool operator<(const xyp &t) const {
    if (t.x == x) return y < t.y;
    return x < t.x;
  }
} ps[MAXN];

set<xyp> s[MAXN];
set<xyp>::iterator it, it2;

void ins(int id, int p) {
  it = s[p].lower_bound(ps[id]);
  if (s[p].begin() != it) {
    it2 = it;
    it2--;
    if (it2->x == ps[id].x && it2->y <= ps[id].y) return;
  }
  for (; it != s[p].end() && it->y >= ps[id].y;) {
    s[p].erase(it++);
  }
  s[p].insert(ps[id]);
}

int check(int id, int p) {
  if (p == -1) return 1;
  it = s[p].lower_bound((xyp) {
      ps[id].x, -inf
  });
  if (it == s[p].begin()) return 0;
  it--;
  return it->y < ps[id].y;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d %d", &ps[i].x, &ps[i].y);
  int len = 0;
  ins(0, 0);
  for (int i = 0; i < n; i++) {
    int l = -1, r = len, mid;
    while (r - l > 1) {
      mid = (l + r) / 2;
      if (check(i, mid)) l = mid;
      else r = mid;
    }
    len = max(len, l + 2);
    ins(i, l + 1);
  }
  printf("%d\n", len);
  return 0;
}

