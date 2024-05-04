#include <string>
#include <iostream>
#include "testlib.h"

long long a, b, c;

int main() {
    registerValidation();

    a = inf.readLong(-1000000000000000000LL, 1000000000000000000LL); inf.readChar(' ');
    b = inf.readLong(-1000000000000000000LL, 1000000000000000000LL); inf.readChar(' ');
    c = inf.readLong(-1000000000000000000LL, 1000000000000000000LL); inf.readChar('\n');

    inf.readEof();
    return 0;
}