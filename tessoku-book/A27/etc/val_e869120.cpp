#include <string>
#include <iostream>
#include "testlib.h"

long long A, B;

int main() {
    registerValidation();

    A = inf.readLong(2LL, 1000000000LL); inf.readChar(' ');
    B = inf.readLong(2LL, 1000000000LL); inf.readChar('\n');

    inf.readEof();
    return 0;
}