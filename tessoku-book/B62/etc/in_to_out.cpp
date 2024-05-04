#include <bits/extc++.h>

int main() {
    using namespace std;
    unsigned long N, M;
    cin >> N >> M;
    vector<vector<unsigned long>> edge(N);
    for(unsigned long i{}, u, v; i < M; ++i){
        cin >> u >> v;
        edge[--u].emplace_back(--v);
        edge[v].emplace_back(u);
    }
    vector<unsigned long> ans, used(N);
    [dfs_impl{[&N, &edge, &ans, &used](auto&& f, unsigned long now, unsigned long prev) -> bool {
        if(now + 1 == N){
            ans.emplace_back(now);
            return true;
        }
        used[now] = 1;
        for(const auto next : edge[now])if(!used[next] && f(f, next, now)){
            ans.emplace_back(now);
            return true;
        }
        return false;
    }}]{dfs_impl(dfs_impl, 0, 0);}();
    reverse(begin(ans), end(ans));
    for(const auto a : ans)cout << a + 1 << " ";
    cout << endl;
    return 0;
}