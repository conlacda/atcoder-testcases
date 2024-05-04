#include <string>
#include <iostream>
#include "testlib.h"

int N, A[100009], B[100009];

int main() {
    registerValidation();

    N = inf.readInt(1, 100000); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        A[i] = inf.readInt(-1000000000, 1000000000); inf.readChar(' ');
        B[i] = inf.readInt(-1000000000, 1000000000); inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}