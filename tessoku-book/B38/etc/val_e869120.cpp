#include <string>
#include <iostream>
#include "testlib.h"

int N;
char c[3009];

int main() {
    registerValidation();

    N = inf.readInt(1, 3000); inf.readChar('\n');
    for (int i = 1; i <= N - 1; i++) {
        c[i] = inf.readChar();
        ensure(c[i] == 'A' || c[i] == 'B');
    }
    inf.readChar('\n');

    inf.readEof();
    return 0;
}