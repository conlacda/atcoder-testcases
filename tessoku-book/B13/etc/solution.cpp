#include <iostream>
#include <vector>
using namespace std;
using lint = long long int;
int main() {
  lint n, k; cin >> n >> k;
  vector<lint> a(n + 1);
  vector<lint> acc(n + 1, 0);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    acc[i + 1] = a[i];
    acc[i + 1] += acc[i];
  }

  lint ans = 0;
  for (int l = 0; l < n; l++) {
    if (a[l] > k) continue;
    lint lb = l;
    lint rb = n;
    while (rb - lb > 1) {
      lint x = (rb + lb) / 2;
      if (acc[x + 1] - acc[l] <= k) lb = x;
      else rb = x;
    }
    ans += lb - l + 1;
  }
  cout << ans << endl;
  return 0;
}
