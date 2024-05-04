#include <string>
#include <map>
#include <iostream>
#include "testlib.h"

int N, P;
long long A[100009];

int main() {
    registerValidation();

    N = inf.readInt(2, 100000); inf.readChar(' ');
    P = inf.readInt(0, 1000000006); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        A[i] = inf.readLong(0LL, 1000000000000000000LL);
        if (i < N) inf.readChar(' ');
        else inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}