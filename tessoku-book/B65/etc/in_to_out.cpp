#include <bits/extc++.h>

int main() {
    using namespace std;
    unsigned long N, T;
    cin >> N >> T;
    --T;
    vector<vector<unsigned long>> edge(N);
    for(unsigned long i{1}, u, v; i < N; ++i){
        cin >> u >> v;
        edge[--u].emplace_back(--v);
        edge[v].emplace_back(u);
    }
    vector<unsigned long> ans(N);
    [dfs_impl{[&edge, &ans](auto&& f, unsigned long now, unsigned long prev) -> unsigned long {
        unsigned long ret{};
        for(const auto next : edge[now])if(next != prev)ret = max(ret, f(f, next, now) + 1);
        return ans[now] = ret;
    }}](unsigned long start){dfs_impl(dfs_impl, start, start);}(T);

    for(const auto a : ans)cout << a << " ";
    cout << endl;
    return 0;
}