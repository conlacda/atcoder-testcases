#include "../../../library/other/template.hpp"
int D, N;
std::vector<int> A;
int main() {
	std::cin >> D >> N;
	A.resize(D);
	rep(i, N) {
		int L, R;
		std::cin >> L >> R;
		L--, R--;
		A[L]++;
		if (R != D - 1) A[R + 1]--;
	}
	rep(i, D - 1) A[i + 1] += A[i];
	rep(i, D) std::cout << A[i] << '\n';
	return 0;
}