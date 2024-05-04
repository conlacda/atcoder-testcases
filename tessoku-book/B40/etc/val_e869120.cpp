#include <string>
#include <iostream>
#include "testlib.h"

int N, A[200009];

int main() {
    registerValidation();

    N = inf.readInt(1, 200000); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        A[i] = inf.readInt(1, 1000000000);
        if (i < N) inf.readChar(' ');
        else inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}