#include <string>
#include <iostream>
#include "testlib.h"

int N, Q;
std::string S;
int L[200009], R[200009];

int main() {
    registerValidation();

    N = inf.readInt(1, 100000); inf.readChar(' ');
    Q = inf.readInt(1, 100000); inf.readChar('\n');
    S = inf.readWord(); inf.readChar('\n');
    for (int i = 0; i < S.size(); i++) {
        ensure('a' <= S[i] && S[i] <= 'z');
    }
    ensure(S.size() == N);

    for (int i = 1; i <= Q; i++) {
        L[i] = inf.readInt(1, N); inf.readChar(' ');
        R[i] = inf.readInt(1, N); inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}