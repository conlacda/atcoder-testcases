#include <string>
#include <iostream>
#include "testlib.h"
using namespace std;

int N;
int L[1 << 19], R[1 << 19];

int main() {
    registerValidation();

    N = inf.readInt(1, 300000); inf.readChar('\n');

    for (int i = 1; i <= N; i++) {
        L[i] = inf.readInt(0, 86400); inf.readChar(' ');
        R[i] = inf.readInt(0, 86400); inf.readChar('\n');
        ensure(L[i] < R[i]);
    }

    inf.readEof();
    return 0;
}