#include <string>
#include <map>
#include <iostream>
#include "testlib.h"

int N, K, L[100009], R[100009];

int main() {
    registerValidation();

    N = inf.readInt(1, 100000); inf.readChar('\n');
    K = inf.readInt(0, 86400); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        L[i] = inf.readInt(0, 86400); inf.readChar(' ');
        R[i] = inf.readInt(0, 86400); inf.readChar('\n');
        ensure(L[i] < R[i]);
    }

    inf.readEof();
    return 0;
}