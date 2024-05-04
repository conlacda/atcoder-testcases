#include <string>
#include <iostream>
#include "testlib.h"

int N, L, R, X[1 << 18];

int main() {
    registerValidation();

    N = inf.readInt(2, 200000); inf.readChar(' ');
    L = inf.readInt(1, 1000000000); inf.readChar(' ');
    R = inf.readInt(1, 1000000000); inf.readChar('\n');
    ensure(L <= R);
    for (int i = 1; i <= N; i++) {
        X[i] = inf.readInt(0, 1000000000);
        if (i < N) inf.readChar(' ');
        else inf.readChar('\n');
    }
    ensure(X[1] == 0);
    for (int i = 2; i <= N; i++) {
        ensure(X[i - 1] < X[i]);
    }

    inf.readEof();
    return 0;
}