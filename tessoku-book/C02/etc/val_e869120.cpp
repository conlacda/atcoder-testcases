#include <string>
#include <map>
#include <iostream>
#include "testlib.h"

int N, A[1009];

int main() {
    registerValidation();

    N = inf.readInt(2, 100); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        A[i] = inf.readInt(1, 1000);
        if (i < N) inf.readChar(' ');
        else inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}