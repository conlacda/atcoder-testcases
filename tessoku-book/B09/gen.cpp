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
		std::cout << N << '\n';
		rep(i, N) {
			int A = mt() % H, B = mt() % W, C = mt() % (H - A) + A, D = mt() % (W - B) + B;
			std::cout << A << ' ' << B << ' ' << C + 1 << ' ' << D + 1 << '\n';
		}
		fclose(f);
	}
	return 0;
}