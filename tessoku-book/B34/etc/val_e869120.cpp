#include <string>
#include <iostream>
#include "testlib.h"

int N, X, Y;
long long A[100009];

int main() {
    registerValidation();

    N = inf.readInt(1, 100000); inf.readChar(' ');
    X = inf.readInt(2, 2); inf.readChar(' ');
    Y = inf.readInt(3, 3); inf.readChar('\n');
    ensure(X < Y);
    for (int i = 1; i <= N; i++) {
        A[i] = inf.readLong(1LL, 1000000000000000000LL);
        if (i < N) inf.readChar(' ');
        else inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}