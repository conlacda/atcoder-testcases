#include "../../../library/other/template.hpp"
int N, Q;
std::vector<int> A;
int main() {
	std::cin >> N >> A >> Q;
	rep(i, N - 1) A[i + 1] += A[i];
	rep(i, Q) {
		int L, R;
		std::cin >> L >> R;
		int c = A[R - 1] - (L != 1 ? A[L - 2] : 0);
		if (c * 2 > R - L + 1)
			puts("win");
		else if (c * 2 == R - L + 1)
			puts("draw");
		else
			puts("lose");
	}
	return 0;
}