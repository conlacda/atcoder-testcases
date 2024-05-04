#include <string>
#include <iostream>
#include "testlib.h"

int N, X[19], Y[19];

int main() {
    registerValidation();

    N = inf.readInt(2, 15); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        X[i] = inf.readInt(0, 1000); inf.readChar(' ');
        Y[i] = inf.readInt(0, 1000); inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}