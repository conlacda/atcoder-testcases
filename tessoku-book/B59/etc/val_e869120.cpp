#include <string>
#include <iostream>
#include "testlib.h"

int N, A[150009];
int cnt[150009];

int main() {
    registerValidation();

    N = inf.readInt(1, 150000); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        A[i] = inf.readInt(1, N);
        if (i < N) inf.readChar(' ');
        else inf.readChar('\n');
        cnt[A[i]] += 1;
    }
    for (int i = 1; i <= N; i++) {
        ensure(cnt[i] == 1);
    }

    inf.readEof();
    return 0;
}