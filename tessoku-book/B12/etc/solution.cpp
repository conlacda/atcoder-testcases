#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool f(long double x, long double n) {
  return x * x * x + x < n;
}

int main() {
  
  long double n; cin >> n;
  long double ok = 0.0;
  long double ng = 1e18;
  for (int i = 0; i < 100100; i++) {
    double x = (ok + ng) / 2.0;
    if (f(x, n)) {
      ok = x;
    } else {
      ng = x;
    }
  }
  printf("%.6Lf\n", ok);
  return 0;
}
