#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 1<<16;

struct segtree {
  struct {
		int sto, opp;
	}	dat[MAX];
	
	int n;
	void init(int _n) {
		n = 1;
		while(n < _n) n *= 2;
		for(int i = 0;i < 2*n;i++)
			dat[i].sto = dat[i].opp = 0;
	}
	void update(int i,int x=0) {
		i += n-1;
		if(x == 0) {
			dat[i].sto ^= 1;
			dat[i].opp ^= 1;
		}else if(x > 0) {
			dat[i].sto = 1;
			dat[i].opp = 0;
		}else {
			dat[i].sto = 0;
			dat[i].opp = 1;
		}
		while(i > 1) {
			i /= 2;
			if(dat[i*2].sto >= dat[i*2+1].opp) {
				dat[i].sto = dat[i*2].sto-dat[i*2+1].opp+dat[i*2+1].sto;
				dat[i].opp = dat[i*2].opp;
			}else {
				dat[i].opp = dat[i*2+1].opp-dat[i*2].sto+dat[i*2].opp;
				dat[i].sto = dat[i*2+1].sto;
			}
		}
	}
	char check() {
		 return dat[1].sto == 0 && dat[1].opp == 0;
	}
} segt;

char str[30003];
int main() {
	int n, q;
	int x;
	for(int tcase = 0;tcase < 10;tcase++) {
		scanf("%d",&n);
		segt.init(n);
		scanf("%s",str);
		for(int i = 0,len=strlen(str);i < len;i++) {
			if(str[i] == '(') segt.update(i+1,1);
			else segt.update(i+1,-1);
		}
		scanf("%d",&q);
		printf("Test %d:\n",tcase+1);
		while(q--) {
			scanf("%d",&x);
			if(!x) {
				if(segt.check()) puts("YES");
				else puts("NO");
			}else segt.update(x);
		}
	}
	return 0;
}
