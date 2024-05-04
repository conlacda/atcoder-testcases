#include <string>
#include <iostream>
#include "testlib.h"

int N, X[100009], Y[100009];

int main() {
    registerValidation();

    N = inf.readInt(1, 100000); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        X[i] = inf.readInt(1, 500000); inf.readChar(' ');
        Y[i] = inf.readInt(1, 500000); inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}