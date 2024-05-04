#include <string>
#include <iostream>
#include "testlib.h"

int N, M, A[200009];

int main() {
    registerValidation();

    N = inf.readInt(1, 200000); inf.readChar(' ');
    M = inf.readInt(1, 200000); inf.readChar('\n');
    for (int i = 1; i <= M; i++) {
        A[i] = inf.readInt(1, N);
        if (i < M) inf.readChar(' ');
        else inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}