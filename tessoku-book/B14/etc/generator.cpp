#include <cstdio>
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <vector>
#include <utility>
#include "xrand.h"
using namespace std;

const int num_of_type = 2;
std::string case_type[num_of_type] = {"10_random_small", "20_random_large"};
int num_of_case[num_of_type] = {15, 15};
using lint = long long int;

XRand rnd(283);

int main() {
    for(int typenum=0;typenum<num_of_type;++typenum){
        for(int casenum=0;casenum<num_of_case[typenum];++casenum){
            std::string file_name = case_type[typenum]+ "_" + (casenum<10?"0":"") + std::to_string(casenum)+".txt";
            std::ofstream output(file_name);
            int n;
            if (typenum == 0) n = rnd.NextInt(1, 16);
            else n = rnd.NextInt(25, 30);
            int k = rnd.NextInt(1, 10000);
            if (rnd.NextInt(1, 10) == 1) k = rnd.NextInt(1, 100000000);
            output << n << " " << k << endl;
            
            vector<lint> a(n);
            for (int i = 0; i < n; i++) {
              int v = rnd.NextInt(1, 10000);
              if (rnd.NextInt(1, 10) == 1) k = rnd.NextInt(1, 100000000);
              a[i] = v;
            }

            // Yes にしたい
            if (true) {
              // かえる id
              int id = rnd.NextInt(0, n - 1);
              // それ以外を適当に足す
              lint sum = 0;
              for (int j = 0; j < n; j++) {
                if (j == id) continue;
                if (rnd.NextInt(0, 5) == 0) {
                  sum += a[j];
                }
              }
              lint need = k - sum;
              if (need <= 0) {
                continue;
              }
              a[id] = need;
            }
            for (int i = 0; i < n; i++) {
              if (i == n - 1) output << a[i] << endl;
              else output << a[i] << " ";
            }

            output.close();
        }
    }
    return 0;
}
