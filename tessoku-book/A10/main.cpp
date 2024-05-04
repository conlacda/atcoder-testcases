#include "../../../library/other/template.hpp"
int N, D;
std::vector<int> A, B;
int main() {
	std::cin >> N >> A;
	B = A;
	rep(i, N - 1) chmax(A[i + 1], A[i]);
	for (int i = N - 1; i > 0; i--) chmax(B[i - 1], B[i]);
	std::cin >> D;
	rep(i, D) {
		int L, R;
		std::cin >> L >> R;
		std::cout << std::max(A[L - 2], B[R]) << '\n';
	}
	return 0;
}
