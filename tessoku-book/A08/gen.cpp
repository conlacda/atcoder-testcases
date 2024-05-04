#include "../../../library/other/template.hpp"
std::random_device rd;
std::mt19937 mt(rd());
int main() {
	rep(i, 5) {
		std::string file_name = "tests/in/random";
		file_name += (i < 10 ? "0" : "") + std::to_string(i);
		file_name += ".txt";
		FILE* f = freopen(file_name.c_str(), "w", stdout);
		const int H = mt() % 1500 + 1, W = mt() % 1500 + 1, Q = mt() % 100000 + 1;
		std::cout << H << ' ' << W << '\n';
		rep(i, H) {
			std::vector<int> Xi(W);
			rep(j, W) Xi[j] = mt() % 10;
			std::cout << Xi << '\n';
		}
		std::cout << Q << '\n';
		rep(i, Q) {
			int A = mt() % H + 1, B = mt() % W + 1, C = mt() % H + 1, D = mt() % W + 1;
			if (A > C) std::swap(A, C);
			if (B > D) std::swap(B, D);
			std::cout << A << ' ' << B << ' ' << C << ' ' << D << '\n';
		}
		fclose(f);
	}
	return 0;
}