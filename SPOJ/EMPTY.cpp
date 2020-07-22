#include <cstdio>
#include <cstring>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int MAXN = 5000;
const ll MX = 1000000;

struct xyp {
  int x, y;

  bool operator<(const xyp &t) const {
    if (t.x == x) return y < t.y;
    return x < t.x;
  }
} ps[MAXN];

set<xyp> s;
set<xyp>::iterator it, it2;

void ins(int id) {
  it = s.lower_bound(ps[id]);
  if (it != s.begin()) {
    it2 = it;
    it2--;
    if (it2->x == ps[id].x && it2->y <= ps[id].y) return;
  }

  for (; it != s.end() && it->y >= ps[id].y;)
    s.erase(it++);

  s.insert(ps[id]);
}

int check(int id) {
  it = s.lower_bound((xyp) {
      ps[id].x, 0
  });
  if (it == s.begin()) return 1;
  it2 = it;
  it2--;
  if (it == s.end()) return it2->y > ps[id].y;
  return (it2->y > ps[id].y && it->y < ps[id].y) || (it->y > ps[id].y);
}

ll ans;
int ansx, ansy, ansz;

void findmax(int z) {
  int lasty = MX;
  for (it = s.begin(); it != s.end(); it++) {
    if ((ll) z * it->x * lasty > ans) {
      ans = (ll) z * it->x * lasty;
      ansx = it->x, ansy = lasty, ansz = z;
    }
    lasty = it->y;
  }
  if ((ll) z * MX * lasty > ans) {
    ans = (ll) z * MX * lasty;
    ansx = MX, ansy = lasty, ansz = z;
  }
}

int z[MAXN];

int cmpz(const int &a, const int &b) {
  return z[a] < z[b];
}

int IND[MAXN];

int main() {
  int t;
  scanf("%d", &t);
  for (int tt = 0; tt < t; tt++) {
    s.clear();
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      scanf("%d %d %d", &ps[i].x, &ps[i].y, z + i);
      IND[i] = i;
    }
    sort(IND, IND + n, cmpz);
    ans = -1;
    ansx = -1, ansy = -1, ansz = -1;
    if (n == 0) {
      ans = (ll) MX * MX * MX;
      ansx = ansy = ansz = MX;
    }
    s.insert((xyp) {
        MX, MX
    });
    for (int i = 0, j; i < n; i = j) {
      findmax(z[IND[i]]);
      for (j = i; j < n && z[IND[i]] == z[IND[j]]; j++)
        if (check(IND[j]))
          ins(IND[j]);
    }
    findmax(MX);
    printf("%d %d %d\n", ansx, ansy, ansz);
  }
  return 0;
}



