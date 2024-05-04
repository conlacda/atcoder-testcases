#include <string>
#include <iostream>
#include "testlib.h"

int A, B;

int main() {
    registerValidation();

    A = inf.readInt(1, 1000000000); inf.readChar(' ');
    B = inf.readInt(1, 1000000000); inf.readChar('\n');

    inf.readEof();
    return 0;
}