#include <string>
#include <iostream>
#include "testlib.h"

std::string N;

int main() {
    registerValidation();

    N = inf.readWord(); inf.readChar();
    ensure(1 <= N.size() && N.size() <= 8);
    for (int i = 0; i < N.size(); i++) {
        ensure('0' <= N[i] && N[i] <= '1');
    }
    ensure(N[0] == '1');

    inf.readEof();
    return 0;
}