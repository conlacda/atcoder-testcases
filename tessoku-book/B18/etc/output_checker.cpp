#include "testlib.h"
#include <bitset>
using namespace std;
void chmin(int& a, int b){ if(a > b) a = b; }

int main(int argc, char * argv[])
{
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    const int N = inf.readInt(1, 60);
    const int S = inf.readInt(1, 10000);
    vector<int> A(N);
    for(int& a : A) a = inf.readInt(1, 10000);

    const bool exist = [&]() -> bool {
        bitset<10048> dp;
        dp[0] = 1;
        for(int a : A) dp |= dp << a;
        return dp[S];
    }();

    const int K = ouf.readInt(-1, N);
    
    if(K == -1){
        if(exist) quit(_wa, "K != -1");
        else quit(_ok, "K == -1");
    }

    vector<int> P(K);
    for(int& a : P) a = ouf.readInt(1, N) - 1;
    sort(P.begin(), P.end());
    if(adjacent_find(P.begin(), P.end()) != P.end()) quit(_wa, "duplicate indices");
    int user_sum = 0;
    for(int a : P) user_sum += A[a];
    quitif(user_sum != S, _wa, "user_sum != S");
    quit(_ok, "user_sum == S");
}
