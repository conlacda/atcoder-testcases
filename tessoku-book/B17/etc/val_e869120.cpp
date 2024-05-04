#include <string>
#include <iostream>
#include "testlib.h"

int N, H[100009];

int main() {
    registerValidation();

    N = inf.readInt(2, 100000); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        H[i] = inf.readInt(1, 10000);
        if (i < N) inf.readChar(' ');
        else inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}