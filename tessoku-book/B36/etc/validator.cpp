#include "testlib.h"
#include <string>

using std::string;

int pow10_9 = 1'000'000'000, pow10_5 = 100'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 3 * pow10_5, "N");
    inf.readSpace();
    inf.readInt(0, N, "K");
    inf.readEoln();
    string S = inf.readString("[01]+", "S");
    ensuref(S.size() == N, "S.len = %d (!= %d)", S.size(), N);
    inf.readEof();
}
