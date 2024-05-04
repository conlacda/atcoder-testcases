#include "testlib.h"

using namespace std;

int main(int argc, char * argv[])
{
    setName("compare sequences of tokens (case insensitive)");
    registerTestlibCmd(argc, argv);

    const auto string_to_lower{[](const string& s){
        string ret{s};
        transform(begin(s), end(s), begin(ret), [](auto c) -> char {if('A' <= c && c <= 'Z')return c + 32; return c;});
        return ret;
    }};

    int n = 0;
    string j, p;

    while (!ans.seekEof() && !ouf.seekEof())
    {
        n++;

        ans.readWordTo(j);
        ouf.readWordTo(p);

        if (string_to_lower(j) != string_to_lower(p))
            quitf(_wa, "%d%s words differ - expected: '%s', found: '%s'", n, englishEnding(n).c_str(), compress(j).c_str(), compress(p).c_str());
    }

    if (ans.seekEof() && ouf.seekEof())
    {
        if (n == 1)
            quitf(_ok, "\"%s\"", compress(j).c_str());
        else
            quitf(_ok, "%d tokens", n);
    }
    else
    {
        if (ans.seekEof())
            quitf(_wa, "Participant output contains extra tokens");
        else
            quitf(_wa, "Unexpected EOF in the participants output");
    }
}
