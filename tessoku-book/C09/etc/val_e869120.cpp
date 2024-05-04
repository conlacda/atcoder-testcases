#include <string>
#include <iostream>
#include "testlib.h"

int N;
int A[1 << 18];

int main() {
    registerValidation();

    N = inf.readInt(2, 500000); inf.readChar('\n');

    for (int i = 1; i <= N; i++) {
        A[i] = inf.readInt(0, 1000000000);
        if (i != N) inf.readChar(' ');
        if (i == N) inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}