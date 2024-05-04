#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int main() {
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  int q; cin >> q;
  for (int i = 0; i < q; i++) {
    int x; cin >> x;
    // x より小さい要素が何個あるか
    // x 以上の最左
    auto itr = lower_bound(a.begin(), a.end(), x);
    cout << itr - a.begin() << endl;
  }
  return 0;
}

