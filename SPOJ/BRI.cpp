#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;
#define sqr(x) ((x)*(x))
#define NLOOP 30
#define csc(x) (1./cos(x))

double a, b, c, h, s1, s2;
double Ae1, sintheta;
double sinphi;

int C(double e1) {
  Ae1 = sqrt(sqr(a) + sqr(e1));
  sintheta = e1 / Ae1;
  sinphi = s1 * sintheta / s2;

  return c <= (e1 + h * tan(asin(sinphi)) + b * tan(asin(sintheta)));
}

double func(double e1) {
  Ae1 = sqrt(sqr(a) + sqr(e1));
  sintheta = e1 / Ae1;
  sinphi = s1 * sintheta / s2;

  return s1 * (Ae1 + b * csc(asin(sintheta))) + s2 * h * csc(asin(sinphi));
}

double bsearch() {
  double l = 0, r = c, mid;
  if (s1 > s2) r = a * tan(asin(s2 / s1));
  for (int i = 0; i < NLOOP; i++) {
    mid = (r + l) * 0.5;
    if (C(mid)) r = mid;
    else l = mid;
  }
  return func(l);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%lf %lf %lf %lf", &a, &b, &c, &h);
    scanf("%lf %lf", &s1, &s2);
    printf("%.2lf\n", bsearch());
  }
  return 0;
}

