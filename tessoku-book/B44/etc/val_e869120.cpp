#include <string>
#include <iostream>
#include "testlib.h"

int N, Q, A[509][509];

int main() {
    registerValidation();

    N = inf.readInt(1, 500); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            A[i][j] = inf.readInt(1, 100);
            if (j < N) inf.readChar(' ');
            else inf.readChar('\n');
        }
    }
    Q = inf.readInt(1, 200000); inf.readChar('\n');
    for (int i = 1; i <= Q; i++) {
        int q1 = inf.readInt(1, 2); inf.readChar(' ');
        int q2 = inf.readInt(1, N); inf.readChar(' ');
        int q3 = inf.readInt(1, N); inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}