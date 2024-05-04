#include <vector>
#include <iostream>
#include "testlib.h"

int main() {
	// step #1. read input
	registerValidation();
	int N = inf.readInt(0, 700000); inf.readChar(' ');
	int L = inf.readInt(1, 700000); inf.readChar(' ');
	int K = inf.readInt(1, 700000); inf.readChar('\n');
	std::vector<int> A(N);
	std::vector<long long> C(N);
	for (int i = 0; i < N; i++) {
		A[i] = inf.readInt(1, L - 1); inf.readChar(' ');
		C[i] = inf.readLong(1LL, 1'000'000'000'000LL); inf.readChar('\n');
	}
	inf.readEof();

	// step #2. check additional constraints
	ensure(K <= L);
	for (int i = 0; i < N - 1; i++) {
		ensure(A[i] <= A[i + 1]);
	}

	return 0;
}