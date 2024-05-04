#include <string>
#include <iostream>
#include "testlib.h"

int N, D;
int X[200009], Y[200009];

int main() {
    registerValidation();

    N = inf.readInt(1, 200000); inf.readChar(' ');
    D = inf.readInt(1, 365); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        X[i] = inf.readInt(1, D); inf.readChar(' ');
        Y[i] = inf.readInt(1, 1000000); inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}