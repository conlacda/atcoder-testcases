#include <string>
#include <iostream>
#include "testlib.h"

int N, Q;
int A[1 << 18];
int L[1 << 18], R[1 << 18];

int X1, Y1, X2, Y2, X3, Y3, X4, Y4;

int main() {
    registerValidation();

    N = inf.readInt(1, 100000); inf.readChar(' ');
    Q = inf.readInt(1, 100000); inf.readChar('\n');

    for (int i = 1; i <= N; i++) {
        A[i] = inf.readInt(1, 10000);
        if (i != N) inf.readChar(' ');
        if (i == N) inf.readChar('\n');
    }

    for (int i = 1; i <= Q; i++) {
        L[i] = inf.readInt(1, N); inf.readChar(' ');
        R[i] = inf.readInt(1, N); inf.readChar('\n');
        ensure(L[i] <= R[i]);
    }

    inf.readEof();
    return 0;
}