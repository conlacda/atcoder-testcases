#include <string>
#include <iostream>
#include "testlib.h"

int N;
std::string S;

int main() {
    registerValidation();

    N = inf.readInt(1, 1000); inf.readChar('\n');
    S = inf.readWord(); inf.readChar('\n');
    for (int i = 0; i < S.size(); i++) {
        ensure('a' <= S[i] && S[i] <= 'z');
    }
    ensure(S.size() == N);

    inf.readEof();
    return 0;
}