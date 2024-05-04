#include <string>
#include <iostream>
#include "testlib.h"

int H, W;

int main() {
    registerValidation();

    H = inf.readInt(1, 100000); inf.readChar(' ');
    W = inf.readInt(1, 100000); inf.readChar('\n');

    inf.readEof();
    return 0;
}