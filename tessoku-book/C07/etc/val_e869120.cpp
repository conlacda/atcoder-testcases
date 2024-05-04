#include <string>
#include <map>
#include <iostream>
#include "testlib.h"

int N, C[100009];
int Q, X[100009];

int main() {
    registerValidation();

    N = inf.readInt(1, 100000); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        C[i] = inf.readInt(1, 10000);
        if (i < N) inf.readChar(' ');
        else inf.readChar('\n');
    }

    Q = inf.readInt(1, 100000); inf.readChar('\n');
    for (int i = 1; i <= Q; i++) {
        X[i] = inf.readInt(1, 1000000000);
        inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}