#include <string>
#include <map>
#include <iostream>
#include "testlib.h"

int N, K;
int A[100009], sum = 0;

int main() {
    registerValidation();

    N = inf.readInt(1, 100000); inf.readChar(' ');
    K = inf.readInt(1, 1000000000); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        A[i] = inf.readInt(1, 1000000000);
        if (i < N) inf.readChar(' ');
        else inf.readChar('\n');
        sum += A[i];
        ensure(0 <= sum && sum <= 1000000000);
    }

    inf.readEof();
    return 0;
}