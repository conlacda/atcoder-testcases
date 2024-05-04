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


const ll N_MAX = 1e5, MAX = 1e4;
int main(int argc, char** argv){
    registerGen(argc, argv, 1);

    auto output = [](ofstream& out, ll N, vector<ll> H){
        out << N << endl;
        out << H << endl;
    };
    
    {
        ofstream out(format("max_%02lld.txt", 1));
        const ll N = N_MAX;
        output(out, N, vector<ll>(N, MAX));
    }
    
    for(ll t_ = 0; t_ < 10; t_++){
        ofstream out(format("small_%02lld.txt", t_ + 1));
        const ll N = 2 + t_ / 2;
        vector<ll> H(N);
        for(ll& a : H) a = rnd.next(1LL, MAX);
        output(out, N, H);
    }
    
    for(ll t_ = 0; t_ < 3; t_++){
        ofstream out(format("large_%02lld.txt", t_ + 1));
        ll N = rnd.next(1LL, N_MAX);
        if(t_ == 0) N = N_MAX;
        vector<ll> H(N);
        for(ll& a : H) a = rnd.next(1LL, MAX);
        output(out, N, H);
    }
}
