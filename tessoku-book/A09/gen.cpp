#include "../../../library/other/template.hpp"
std::random_device rd;
std::mt19937 mt(rd());
int main() {
	rep(i, 1) {
		std::string file_name = "tests/in/max";
		file_name += (i < 10 ? "0" : "") + std::to_string(i);
		file_name += ".txt";
		FILE* f = freopen(file_name.c_str(), "w", stdout);
		const int H = 1500, W = 1500, N = 100000;
		std::cout << H << ' ' << W << ' ' << N << '\n';
		rep(i, N) {
			int A = mt() % H + 1, B = mt() % W + 1, C = mt() % H + 1, D = mt() % W + 1;
			if (A > C) std::swap(A, C);
			if (B > D) std::swap(B, D);
			std::cout << A << ' ' << B << ' ' << C << ' ' << D << '\n';
		}
		fclose(f);
	}
	return 0;
}