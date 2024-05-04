#include <string>
#include <iostream>
#include "testlib.h"

int T, N;
int L[1 << 19];
int R[1 << 19];

int main() {
    registerValidation();

    T = inf.readInt(1, 500000); inf.readChar('\n');
    N = inf.readInt(1, 500000); inf.readChar('\n');
    
    for (int i = 1; i <= N; i++) {
        L[i] = inf.readInt(0, T); inf.readChar(' ');
        R[i] = inf.readInt(0, T); inf.readChar('\n');
        ensure(L[i] < R[i]);
    }

    inf.readEof();
    return 0;
}