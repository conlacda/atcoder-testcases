#include "../../../library/other/template.hpp"
int H, W, Q;
int main() {
	std::cin >> H >> W;
	auto X = make_vec<int>(H, W);
	rep(i, H) rep(j, W) std::cin >> X[i][j];
	rep(i, H) rep(j, W - 1) X[i][j + 1] += X[i][j];
	rep(i, H - 1) rep(j, W) X[i + 1][j] += X[i][j];
	std::cin >> Q;
	rep(i, Q) {
		int A, B, C, D;
		std::cin >> A >> B >> C >> D;
		A--, B--, C--, D--;
		int ans = X[C][D];
		if (A) ans -= X[A - 1][D];
		if (B) ans -= X[C][B - 1];
		if (A && B) ans += X[A - 1][B - 1];
		std::cout << ans << '\n';
	}
	return 0;
}