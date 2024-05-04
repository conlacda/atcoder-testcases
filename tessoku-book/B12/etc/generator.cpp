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
int num_of_case[num_of_type] = {10, 10};

XRand rnd(283);

int main() {
    for(int typenum=0;typenum<num_of_type;++typenum){
        for(int casenum=0;casenum<num_of_case[typenum];++casenum){
            std::string file_name = case_type[typenum]+ "_" + (casenum<10?"0":"") + std::to_string(casenum)+".txt";
            std::ofstream output(file_name);
            int n;
            if (typenum == 0) n = rnd.NextInt(1, 100);
            else n = rnd.NextInt(100, 100000);
            output << n << endl;
            output.close();
        }
    }
    return 0;
}
