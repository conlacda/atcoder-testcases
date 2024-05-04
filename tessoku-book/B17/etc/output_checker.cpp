#include "testlib.h"
using namespace std;
void chmin(int& a, int b){ if(a > b) a = b; }

int main(int argc, char * argv[])
{
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    int N = inf.readInt(2, 100000);
    vector<int> H(N);
    for(int& a : H) a = inf.readInt(1, 10000);

    const int min_cost = [&]{
        vector<int> dp(N, 1 << 30);
        dp[0] = 0;
        for(int i = 0; i < N - 1; i++){
            if(i + 2 < N) chmin(dp[i + 2], dp[i] + abs(H[i] - H[i + 2]));
            chmin(dp[i + 1], dp[i] + abs(H[i] - H[i + 1]));
        }
        return dp.back();
    }();

    const int K = ouf.readInt(2, N);
    vector<int> P(K);
    for(int& a : P) a = ouf.readInt(1, N) - 1;
    quitif(P.front() != 0, _wa, "P.front() != 0");
    quitif(P.back() != N - 1, _wa, "P.back() != N - 1");
    int user_cost = 0;
    for(int i = 0; i + 1 < K; i++){
        const int d = P[i + 1] - P[i];
        if(d == 1 || d == 2) user_cost += abs(H[P[i]] - H[P[i + 1]]);
        else quit(_wa, "d not in [1, 2]");
    }
    quitif(min_cost != user_cost, _wa, "min_cost != user_cost");
    quit(_ok, "");
}
