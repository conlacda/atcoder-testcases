#include <string>
#include <iostream>
#include "testlib.h"

int N, K, A[100009];

int main() {
    registerValidation();

    N = inf.readInt(1, 100000); inf.readChar(' ');
    K = inf.readInt(1, 100); inf.readChar('\n');
    for (int i = 1; i <= K; i++) {
        A[i] = inf.readInt(1, 100000);
        if (i < K) inf.readChar(' ');
        else inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}