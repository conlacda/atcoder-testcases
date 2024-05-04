#include "testlib.h"

int pow10_9 = 1'000'000'000, pow10_5 = 100'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 3000, "N");
    inf.readEoln();
    inf.readString(format("[AB]{%d}", N - 1), "S");
    inf.readEof();
}
