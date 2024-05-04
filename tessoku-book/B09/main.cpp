#include "../../../library/other/template.hpp"
int N;
int main() {
	std::cin >> N;
	auto vec = make_vec<int>(1501, 1501);
	rep(i, N) {
		int A, B, C, D;
		std::cin >> A >> B >> C >> D;
		vec[A][B]++;
		vec[C][B]--;
		vec[A][D]--;
		vec[C][D]++;
	}
	rep(i, 1501) rep(j, 1500) vec[i][j + 1] += vec[i][j];
	rep(i, 1500) rep(j, 1501) vec[i + 1][j] += vec[i][j];
	int ans = 0;
	rep(i, 1501) rep(j, 1501) if (vec[i][j]) ans++;
	std::cout << ans << '\n';
	return 0;
}