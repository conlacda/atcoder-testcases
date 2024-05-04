#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


// naive
int main() {
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int q; cin >> q;
  for (int i = 0; i < q; i++) {
    int x; cin >> x;
    int ans = 0;
    for (auto ii : a) if (ii < x) ans++;
    cout << ans << endl;
  }
  return 0;
}

