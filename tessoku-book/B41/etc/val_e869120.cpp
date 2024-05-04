#include <string>
#include <iostream>
#include "testlib.h"

int X, Y;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int main() {
    registerValidation();

    X = inf.readInt(1, 1000000); inf.readChar(' ');
    Y = inf.readInt(1, 1000000); inf.readChar('\n');
    ensure(gcd(X, Y) == 1);

    inf.readEof();
    return 0;
}