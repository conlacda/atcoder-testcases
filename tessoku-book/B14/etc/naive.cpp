#include <iostream>
#include <vector>
using namespace std;
using lint = long long int;
int main() {
  lint n, k; cin >> n >> k;
  vector<lint> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int bit = 0; bit < (1 << n); bit++) {
    lint sum = 0;
    for (int i = 0; i < n; i++) {
      if ((1 << i) & bit) sum += a[i];
    }
    if (sum == k) {
      cout << "Yes" << endl;
      return 0;
    }
  }


  cout << "No" << endl;
  return 0;
}
