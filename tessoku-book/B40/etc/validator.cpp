#include "testlib.h"

int pow10_9 = 1'000'000'000, pow10_5 = 100'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int N = inf.readInt(1, 2 * pow10_5, "N");
    inf.readEoln();
    for (int i = 0; i < N; i++)
    {
        inf.readInt(1, pow10_9, "A_i");
        if (i < N - 1) inf.readSpace();
        else inf.readEoln();
    }
    inf.readEof();
}
