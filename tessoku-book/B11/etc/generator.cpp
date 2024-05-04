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
#include "constraints.hpp"
using namespace std;

const int num_of_type = 2;
std::string case_type[num_of_type] = {"10_random_small", "20_random_large"};
int num_of_case[num_of_type] = {10, 10};

XRand rnd(283);

int main() {
    for(int typenum=0;typenum<num_of_type;++typenum){
        for(int casenum=0;casenum<num_of_case[typenum];++casenum){
            std::string file_name = case_type[typenum]+ "_0" + std::to_string(casenum)+".txt";
            std::ofstream output(file_name);
            int n;
            if (typenum == 0) n = rnd.NextInt(MIN_N, 100);
            else n = rnd.NextInt(50000, MAX_N);
            vector<int> a(n);
            for (int i = 0; i < n; i++) {
              a[i] = rnd.NextInt(MIN_A, MAX_A);
            }
            output << n << endl;
            for (int i = 0; i < n; i++) {
              if (i == n - 1) output << a[i] << endl;
              else output << a[i] << " ";
            }

            int q;
            if (typenum == 0) q = rnd.NextInt(MIN_N, 100);
            else q = rnd.NextInt(50000, MAX_N);
            output << q << endl;
            for (int i = 0; i < q; i++) {
              output << rnd.NextInt(0, MAX_A) << endl;
            }
            output.close();
        }
    }
    return 0;
}
