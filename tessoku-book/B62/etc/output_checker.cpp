#include <unordered_set>

#include "testlib.h"

int main(int argc, char * argv[]){
    using namespace std;

    setName("check if output is a simple path from 1 to N");
    registerTestlibCmd(argc, argv);

    unordered_set<unsigned long> edge_set;

    const auto rolling_hash{[](const string& s){
        unsigned long ret{};
        for(const auto c : s){
            unsigned long z{ret + c + 11400714819323198485UL};
            z = (z ^ (z >> 30UL)) * 13787848793156543929UL;
            z = (z ^ (z >> 27UL)) * 10723151780598845931UL;
            ret ^= z ^ (z >> 31UL);
        }
        return ret;
    }};
    const auto edge_hash{[&rolling_hash](const string& u, const string& v){
        return rolling_hash(u) ^ rolling_hash(v);
    }};

    string inf_N, inf_M;
    string inf_string_0, inf_string_1;
    inf.readTokenTo(inf_N);
    inf.readTokenTo(inf_M);
    while(!inf.seekEof()){
        inf.readTokenTo(inf_string_0);
        inf.readTokenTo(inf_string_1);
        edge_set.insert(edge_hash(inf_string_0, inf_string_1));
    }

    string ouf_1;
    ouf.readTokenTo(ouf_1);
    if(ouf_1 != "1")
        quitf(_wa, "start must be 1 but %s", ouf_1.c_str());
    string ouf_string_first{ouf_1}, ouf_string_second;
    while(!ouf.seekEof()){
        ouf.readTokenTo(ouf_string_second);
        if(!edge_set.count(edge_hash(ouf_string_first, ouf_string_second)))
            quitf(_wa, "edge (%s, %s) is not in edge list", ouf_string_first.c_str(), ouf_string_second.c_str());
        swap(ouf_string_first, ouf_string_second);
    }
    if(ouf_string_first != inf_N)
        quitf(_wa, "end must be %s but %s", inf_N.c_str(), ouf_string_first.c_str());


    quitf(_ok, "simple path from 1 to %s", inf_N.c_str());
}