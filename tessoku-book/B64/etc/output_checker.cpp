#include <unordered_map>

#include "testlib.h"

int main(int argc, char * argv[]){
    using namespace std;

    setName("check if output is a shortest path from 1 to N");
    registerTestlibCmd(argc, argv);

    unordered_map<unsigned long, unsigned long> edge_set;

    const auto rolling_hash{[](const unsigned long& s){
        unsigned long z{s + 11400714819323198485UL};
        z = (z ^ (z >> 30UL)) * 13787848793156543929UL;
        z = (z ^ (z >> 27UL)) * 10723151780598845931UL;
        return z;
    }};
    const auto edge_hash{[&rolling_hash](const unsigned long& u, const unsigned long& v){
        return rolling_hash(u) ^ rolling_hash(v);
    }};

    const auto inf_N{inf.readUnsignedLong(2, 100000)};
    const auto inf_M{inf.readUnsignedLong(1, min<decltype(inf_N)>(100000, inf_N * (inf_N - 1) / 2))};
    while(!inf.seekEof()){
        const auto u{inf.readUnsignedLong(1, inf_N)};
        const auto v{inf.readUnsignedLong(u + 1, inf_N)};
        const auto c{inf.readUnsignedLong(1, 10000)};
        edge_set[edge_hash(u - 1, v - 1)] = c;
    }

    vector<unsigned long> dist;
    while(!ans.seekEof())dist.emplace_back(ans.readUnsignedLong());

    unsigned long path_first{ouf.readUnsignedLong()}, path_second{};
    if(path_first != 1)
        quitf(_wa, "start must be 1 but %lu", path_first);
    while(!ouf.seekEof()){
        path_second = ouf.readUnsignedLong();
        const auto c{edge_set[edge_hash(path_first - 1, path_second - 1)]};
        if(dist[path_first - 1] + c != dist[path_second - 1])
            quitf(_wa, "given path is not a shortest path");
        swap(path_first, path_second);
    }
    if(path_first != inf_N)
        quitf(_wa, "end must be %llu but %lu", inf_N, path_first);

    quitf(_ok, "simple path from 1 to %llu", inf_N);
}