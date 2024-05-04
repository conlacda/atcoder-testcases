#include <unordered_set>

#include "testlib.h"

int main(int argc, char * argv[]){
    using namespace std;

    setName("check if answer includes output");
    registerTestlibCmd(argc, argv);

    unordered_set<unsigned long> ans_set;

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

    while(!ans.seekEof())ans_set.insert(rolling_hash(ans.readToken()));
    unsigned long n;
    string ouf_string;
    while(!ouf.seekEof()){
        ++n;
        ouf.readTokenTo(ouf_string);
        if(!ans_set.count(rolling_hash(ouf_string)))
            quitf(_wa, "%s is not in ans", ouf_string.c_str());
    }

    if(n == 1)
        quitf(_ok, "%s is in ans", ouf_string.c_str());
    else
        quitf(_wa, "unexpected tokens : there is %lu tokens", n);
}