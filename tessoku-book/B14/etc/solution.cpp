#include <iostream>
#include <vector>
#include <set>

using namespace std;
using lint = long long int;

int main() {
  lint n, k; cin >> n >> k;
  if (n <= 2) {
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



  // begin
  vector<lint> a;
  vector<lint> b;
  for (int i = 0; i < n; i++) {
    int v; cin >> v;
    if (i % 2 == 0) a.push_back(v);
    else b.push_back(v);
  }

  set<lint> red;
  {
    int m = a.size();
    for (int bit = 0; bit < (1 << m); bit++) {
      lint sum = 0;
      for (int i = 0; i < m; i++) {
        if ((1 << i) & bit) sum += a[i];
      }
      red.insert(sum);
    }
  }
  set<int> blue;
  {
    int m = b.size();
    for (int bit = 0; bit < (1 << m); bit++) {
      lint sum = 0;
      for (int i = 0; i < m; i++) {
        if ((1 << i) & bit) sum += b[i];
      }
      blue.insert(sum);
    }
  }


  for (auto itr : red) {
    int val = k - itr;
    if (blue.count(val)) {
      cout << "Yes" << endl;
      return 0;
    }
  }

  cout << "No" << endl;
  return 0;
}
