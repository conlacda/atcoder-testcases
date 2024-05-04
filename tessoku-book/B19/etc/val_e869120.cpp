#include <string>
#include <iostream>
#include "testlib.h"

int N, W, w[10009], v[10009];

int main() {
    registerValidation();

    N = inf.readInt(1, 100); inf.readChar(' ');
    W = inf.readInt(1, 1000000000); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        w[i] = inf.readInt(1, W); inf.readChar(' ');
        v[i] = inf.readInt(1, 1000); inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}