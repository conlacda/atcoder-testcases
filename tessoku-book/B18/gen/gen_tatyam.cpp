#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
#define all(a) begin(a), end(a)
#define each(i, a) for(auto&& i : a)
ll rand_exp(ll lo, ll hi){
    assert(1 <= lo && lo <= hi && hi < 1LL << 45);
    const double ans = exp(rnd.next(log(lo), log(hi + 1)));
    return clamp<ll>(ans, lo, hi);
}
template<class T> ofstream& operator<<(ofstream& os, const vector<T>& vec){ const int N = vec.size(); for(int i = 0; i < N; i++){ os << vec[i] << (i + 1 == N ? "" : " "); } return os; }


const ll N_MAX = 60, MAX = 1e4;
int main(int argc, char** argv){
    registerGen(argc, argv, 1);

    auto output = [](ofstream& out, ll N, ll S, vector<ll> A){
        out << N << ' ' << S << endl;
        out << A << endl;
    };
    
    for(ll t_ = 0; t_ < 3; t_++){
        ofstream out(format("max_%02lld.txt", t_ + 1));
        const ll N = N_MAX;
        const ll S = vector<ll>{1, MAX, MAX / N * N}[t_];
        vector<ll> A(N, vector<ll>{MAX, MAX, MAX / N}[t_]);
        output(out, N, S, A);
    }
    
    for(ll t_ = 0; t_ < 10; t_++){
        ofstream out(format("small_%02lld.txt", t_ + 1));
        const ll N = t_ + 1, S = rnd.next(1LL, t_ * 5 + 2);
        vector<ll> A(N);
        for(ll& a : A) a = rnd.next(1LL, t_ * 5 + 2);
        output(out, N, S, A);
    }
    
    for(ll t_ = 0; t_ < 5; t_++){
        ofstream out(format("large_%02lld.txt", t_ + 1));
        ll N = rnd.next(1LL, N_MAX);
        const ll S = rnd.next(1LL, MAX);
        if(t_ == 0) N = N_MAX;
        const ll max = rand_exp(S * 2 / N + 1, MAX);
        vector<ll> A(N);
        for(ll& a : A) a = rnd.next(1LL, max);
        output(out, N, S, A);
    }
}
