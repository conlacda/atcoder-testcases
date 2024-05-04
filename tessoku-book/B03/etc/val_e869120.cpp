#include <string>
#include <iostream>
#include "testlib.h"

int N, A[10009];

int main() {
    registerValidation();
    
    N = inf.readInt(3, 100); inf.readChar('\n');
    for (int i = 1; i <= N; i++) {
        A[i] = inf.readInt(1, 1000);
        if (i < N) inf.readChar(' ');
        else inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}