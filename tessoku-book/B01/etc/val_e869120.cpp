#include <string>
#include <iostream>
#include "testlib.h"

int main() {
    registerValidation();

    int A = inf.readInt(1, 100); inf.readChar(' ');
    int B = inf.readInt(1, 100); inf.readChar('\n');
    inf.readEof();
    return 0;
}