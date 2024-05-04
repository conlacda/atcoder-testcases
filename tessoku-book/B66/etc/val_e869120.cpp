#include <string>
#include <map>
#include <iostream>
#include "testlib.h"

int N, M, A[100009], B[100009];
int Q, q1[100009], q2[100009], q3[100009];

int main() {
    registerValidation();

    N = inf.readInt(2, 100000); inf.readChar(' ');
    M = inf.readInt(1, 100000); inf.readChar('\n');
    for (int i = 1; i <= M; i++) {
        A[i] = inf.readInt(1, N); inf.readChar(' ');
        B[i] = inf.readInt(1, N); inf.readChar('\n');
        ensure(A[i] < B[i]);
    }

    Q = inf.readInt(1, 100000); inf.readChar('\n');
    for (int i = 1; i <= Q; i++) {
        q1[i] = inf.readInt(1, 2);
        if (q1[i] == 1) {
            inf.readChar(' '); q2[i] = inf.readInt(1, M);
            inf.readChar('\n');
        }
        if (q1[i] == 2) {
            inf.readChar(' '); q2[i] = inf.readInt(1, N);
            inf.readChar(' '); q3[i] = inf.readInt(1, N);
            inf.readChar('\n');
            ensure(q2[i] < q3[i]);
        }
    }

    inf.readEof();
    return 0;
}