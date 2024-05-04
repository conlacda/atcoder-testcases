#include <string>
#include <iostream>
#include "testlib.h"

int N, K;
char c[300009];

int main() {
    registerValidation();

    N = inf.readInt(2, 300000); inf.readChar(' ');
    K = inf.readInt(0, N); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        c[i] = inf.readChar();
        ensure(c[i] == '1' || c[i] == '0');
    }
    inf.readChar('\n');

    inf.readEof();
    return 0;
}