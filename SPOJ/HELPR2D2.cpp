#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int inf = 0x7fffffff;
const int MAXN = 1<<20;


struct segtree {
  int dat[MAXN*2];
	int n;
	void init(int _n) {
		n = 1; while(_n > n) n*=2;
		for(int i = 1;i < 2*n;i++) dat[i] = -1;
	}
	int update(int i,int x) {
		i += n-1;
		dat[i] = x;
		for(i/=2;i > 1;i/=2) dat[i]=max(dat[i*2],dat[i*2+1]);
	}
	void update2(int k,int lb) {
		if(k >= n) update(k-n+1,dat[k]-lb);
		else if(dat[k*2] >= lb) update2(k*2,lb);
		else update2(k*2+1,lb);
	}
	void compute(int &uss,int &tot,int k) {
		uss = tot = 0;
		for(int i = n;i < 2*n;i++) {
			if(dat[i] != k && dat[i] != -1) {
				uss++;
				tot += dat[i];
			}
		}
	}
} segt;

int main(void) {
	int t, k, n, r, nv;
	int uss, tot;
	char input[100];
	scanf("%d",&t);
	while(t--) {
		scanf("%d %d",&k,&n);
		segt.init(n);
		for(int i = 0;i < n;i++) segt.update(i+1,k);
		for(int i = 0;i < n;i++) {
			scanf("%s",input);
			if(strchr(input,'b')!=NULL) {
				scanf("%d%d",&r,&nv);
				while(r--) { segt.update2(1,nv); i++; }
				i--;
			}else {
				nv = atoi(input);
				segt.update2(1,nv);
			}
		}
		segt.compute(uss,tot,k);
		printf("%d %d\n",uss,tot);
	}
	return 0;
}
