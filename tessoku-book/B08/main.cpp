#include "../../../library/other/template.hpp"
int N, Q;
auto vec = make_vec<int>(1500, 1500);
int main() {
	std::cin >> N;
	rep(i, N) {
		int X, Y;
		std::cin >> X >> Y;
		vec[X - 1][Y - 1]++;
	}
	rep(i, 1499) rep(j, 1500) vec[i + 1][j] += vec[i][j];
	rep(i, 1500) rep(j, 1499) vec[i][j + 1] += vec[i][j];
	std::cin >> Q;
	rep(i, Q) {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		a--, b--, c--, d--;
		int ans = vec[c][d];
		if (a) ans -= vec[a - 1][d];
		if (b) ans -= vec[c][b - 1];
		if (a && b) ans += vec[a - 1][b - 1];
		std::cout << ans << '\n';
	}
	return 0;
}