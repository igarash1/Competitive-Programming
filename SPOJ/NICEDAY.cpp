#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
const int MAXN = 100000;

struct Tuple {
    int x, y, z;
} P[MAXN];

struct Pair {
    int x, y;
    bool operator<(const Pair &t) const {
        return x < t.x;
    }
} p;

bool cmp3d(const Tuple &a,const Tuple &b) {
    return a.z < b.z;
}

set<Pair> S;

bool check(set<Pair>::iterator it,Pair &p) {
    set<Pair>::iterator it2 = it;
    it2--;
    if(it == S.end()) return it2->y > p.y;
    return (it2->y > p.y && p.y > it->y)||(it->y > p.y);
}

int main() {
    int t;
    scanf("%d",&t);

    while(t--) {
        int N;
        scanf("%d",&N);
        for(int i = 0; i < N; i++)
            scanf("%d %d %d",&P[i].x,&P[i].y,&P[i].z);

        sort(P,P+N,cmp3d);

        S.clear();
        set<Pair>::iterator it;
        int ans = 0;

        for(int i = 0; i < N; i++) {
            p.x = P[i].x;
            p.y = P[i].y;
            it = S.lower_bound(p);

            if(it == S.begin() || check(it,p)) {
                ans++;

                for(; it != S.end()&&it->y > p.y;)
                    S.erase(it++);

                S.insert(p);
            }
        }

        printf("%d\n",ans);
    }

    return 0;
}
