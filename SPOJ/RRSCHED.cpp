#include <cstdio>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;

struct TIX {
  int v;
  int ix;

  bool operator<(const TIX &t) const {
    if (v == t.v) return ix > t.ix;
    return v > t.v;
  }
};

int n;

int bit[50001];

void update(int i, int x) {
  for (; i <= n; i += i & -i) bit[i] += x;
}

int sum(int i) {
  int s = 0;
  for (; i > 0; i -= i & -i) s += bit[i];
  return s;
}

priority_queue<TIX> pq;
ll ans[500000];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    TIX t;
    scanf("%d", &t.v);
    t.ix = i + 1;
    update(i + 1, 1);
    pq.push(t);
  }
  int preh = 0;
  ll curs = 0;
  while (!pq.empty()) {
    TIX t = pq.top();
    curs += ll(t.v - preh - 1) * ll(pq.size());
    int tr;
    for (tr = 0; !pq.empty() && t.v == pq.top().v; tr++) {
      int ix = pq.top().ix;
      ans[ix - 1] = curs + ll(sum(ix) + tr);
      update(ix, -1);
      pq.pop();
    }
    curs += tr;
    preh = t.v - 1;
  }
  for (int i = 0; i < n; i++) printf("%lld\n", ans[i]);
  return 0;
}
