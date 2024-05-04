#include "../../../library/other/template.hpp"
int H, W, N;
int main() {
	std::cin >> H >> W >> N;
	auto vec = make_vec<int>(H, W);
	rep(i, N) {
		int A, B, C, D;
		std::cin >> A >> B >> C >> D;
		A--, B--, C--, D--;
		vec[A][B]++;
		if (C != H - 1) vec[C + 1][B]--;
		if (D != W - 1) vec[A][D + 1]--;
		if (C != H - 1 && D != W - 1) vec[C + 1][D + 1]++;
	}
	rep(i, H) rep(j, W - 1) vec[i][j + 1] += vec[i][j];
	rep(i, H - 1) rep(j, W) vec[i + 1][j] += vec[i][j];
	rep(i, H) std::cout << vec[i] << '\n';
	return 0;
}