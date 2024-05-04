#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using lint = long long int;

int main() {
  int n, k; cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  lint ans = 0;
  for (int l = 0; l < n; l++) {
    for (int r = l; r < n; r++) {
      lint sum = 0;
      for (int i = l; i <= r; i++) {
        sum += a[i];
      }
      if (sum <= k) ans++;
    }
  }
  cout << ans << endl;
  return 0;
}

