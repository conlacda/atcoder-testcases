#include <string>
#include <map>
#include <iostream>
#include "testlib.h"

int N, M, A[100009], B[100009], C[100009];
std::map<std::pair<int, int>, int> Map;

int main() {
    registerValidation();

    N = inf.readInt(2, 100000); inf.readChar(' ');
    M = inf.readInt(1, 100000); inf.readChar('\n');
    for (int i = 1; i <= M; i++) {
        A[i] = inf.readInt(1, N); inf.readChar(' ');
        B[i] = inf.readInt(1, N); inf.readChar(' ');
        C[i] = inf.readInt(1, 10000); inf.readChar('\n');
        ensure(A[i] < B[i]);
        ensure(Map[std::make_pair(A[i], B[i])] == 0);
        Map[std::make_pair(A[i], B[i])] = 1;
    }

    inf.readEof();
    return 0;
}