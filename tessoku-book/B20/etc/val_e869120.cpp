#include <string>
#include <iostream>
#include "testlib.h"

std::string S, T;

int main() {
    registerValidation();

    S = inf.readWord(); inf.readChar('\n');
    T = inf.readWord(); inf.readChar('\n');
    ensure(1 <= S.size() && S.size() <= 2000);
    ensure(1 <= T.size() && T.size() <= 2000);
    for (int i = 0; i < S.size(); i++) {
        ensure('a' <= S[i] && S[i] <= 'z');
    }
    for (int i = 0; i < T.size(); i++) {
        ensure('a' <= T[i] && T[i] <= 'z');
    }

    inf.readEof();
    return 0;
}