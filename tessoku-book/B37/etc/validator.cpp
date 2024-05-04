#include "testlib.h"

int pow10_9 = 1'000'000'000, pow10_5 = 100'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    inf.readLong(1LL, 1'000'000'000'000'000LL - 1, "N");
    inf.readEoln();
    inf.readEof();
}
