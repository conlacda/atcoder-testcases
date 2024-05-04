#include <bits/extc++.h>

int main() {
    using namespace std;
    unsigned long N, M, Q;
    cin >> N >> M;
    vector<unsigned long> uf(N), sz(N, 1);
    iota(begin(uf), end(uf), 0UL);
    const auto find{[&uf](auto i){while(i != uf[i])i = uf[i] = uf[uf[i]]; return i;}};
    const auto unite{[&uf, &sz, &find](auto i, auto j){
        i = find(i);
        j = find(j);
        if(i == j)return;
        if(sz[i] < sz[j])swap(i, j);
        sz[i] += sz[j];
        uf[j] = i;
    }};
    vector<pair<unsigned long, unsigned long>> edges(M);
    for(auto&& [u, v] : edges){
        cin >> u >> v;
        --u;
        --v;
    }
    cin >> Q;
    vector<tuple<unsigned long, unsigned long, unsigned long>> queries(Q);
    set<unsigned long> broken_railway;
    for(unsigned long i{}; i < M; ++i)broken_railway.emplace(i);
    for(auto&& [t, u, v] : queries){
        cin >> t;
        if(t == 1){
            cin >> u;
            --u;
            broken_railway.erase(u);
        }else{
            cin >> u >> v;
            --u;
            --v;
        }
    }
    for(const auto idx : broken_railway)queries.emplace_back(1, idx, 0);
    reverse(begin(queries), end(queries));
    vector<unsigned long> ans;
    for(const auto [t, u, v] : queries){
        if(t == 1)unite(edges[u].first, edges[u].second);
        else ans.emplace_back(find(u) == find(v));
    }
    reverse(begin(ans), end(ans));
    for(const auto b : ans)cout << (b ? "Yes" : "No") << endl;
    return 0;
}