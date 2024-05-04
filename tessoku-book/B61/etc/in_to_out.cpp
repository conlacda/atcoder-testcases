#include <bits/extc++.h>

int main() {
    using namespace std;
    unsigned long N, M;
    cin >> N >> M;
    vector<vector<unsigned long>> edge(N);
    unsigned long mx_size{};
    for(unsigned long i{}, u, v; i < M; ++i){
        cin >> u >> v;
        edge[--u].emplace_back(--v);
        edge[v].emplace_back(u);
        mx_size = max({mx_size, size(edge[u]), size(edge[v])});
    }
    for(unsigned long i{}; i < N; ++i)if(size(edge[i]) == mx_size)cout << i + 1 << endl;
    return 0;
}