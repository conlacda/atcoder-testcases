#include <string>
#include <map>
#include <iostream>
#include "testlib.h"
using namespace std;

int N, M;
int A[1 << 18], B[1 << 18];
map<pair<int, int>, int> Map;

int main() {
    registerValidation();

    N = inf.readInt(1, 100000); inf.readChar(' ');
    M = inf.readInt(0, 100000); inf.readChar('\n');

    for (int i = 1; i <= M; i++) {
        A[i] = inf.readInt(1, N); inf.readChar(' ');
        B[i] = inf.readInt(1, N); inf.readChar('\n');
        ensure(A[i] != B[i]);

        if (A[i] > B[i]) swap(A[i], B[i]);
        ensure(Map[make_pair(A[i], B[i])] == 0);
        Map[make_pair(A[i], B[i])] = 1;
    }

    inf.readEof();
    return 0;
}