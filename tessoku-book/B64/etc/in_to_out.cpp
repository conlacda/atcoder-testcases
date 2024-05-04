#include <bits/extc++.h>

template<class T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<>>;

int main() {
    using namespace std;
    unsigned long N, M;
    cin >> N >> M;
    vector<vector<pair<unsigned long, unsigned long>>> edge(N);
    for(unsigned long i{}, u, v, c; i < M; ++i){
        cin >> u >> v >> c;
        edge[--u].emplace_back(--v, c);
        edge[v].emplace_back(u, c);
    }
    min_heap<pair<unsigned long, unsigned long>> pq;
    vector<unsigned long> dist(N, numeric_limits<unsigned long>::max());
    pq.emplace(dist[0] = 0, 0);
    while(!pq.empty()){
        const auto [distance, now]{pq.top()};
        pq.pop();
        if(dist[now] < distance)continue;
        for(const auto [next, cost] : edge[now])if(dist[next] > distance + cost)pq.emplace(dist[next] = distance + cost, next);
    }
    for(const auto d : dist)cout << static_cast<long>(d) << endl;
    return 0;
}