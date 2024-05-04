#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
#define all(a) begin(a), end(a)
#define space inf.readChar(' ')
#define endl inf.readChar('\n')
#define eof inf.readEof()
tuple<ll> read(ll min, ll max){
    ll a = inf.readLong(min, max);
    endl;
    return tuple{a};
}
template<class... T> auto read(ll min, ll max, T... t){
    ll a = inf.readLong(min, max);
    space;
    return tuple_cat(tuple{a}, read(t...));
}
string read(string p){
    return inf.readLine(p);
}
vector<ll> reads(ll N, ll min, ll max){
    auto a = inf.readLongs(N, min, max);
    endl;
    return a;
}
vector<string> read_lines(ll N, string p){
    return inf.readLines(N, p);
}
template<class... T> auto read_lines(ll N, T... t){
    vector<decltype(read(t...))> a;
    a.reserve(N);
    while(N--) a.push_back(read(t...));
    return a;
}
vector<vector<ll>> read_matrix(ll H, ll W, ll min, ll max){
    vector<vector<ll>> ans(H);
    for(auto& v : ans) v = reads(W, min, max);
    return ans;
}


int main(){
    registerValidation();
    auto [N] = read(3, 100000);
    reads(N - 1, 1, 100);
    reads(N - 2, 1, 100);
    eof;
}
