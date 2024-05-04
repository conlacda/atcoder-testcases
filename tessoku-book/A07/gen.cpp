#include "../../../library/other/template.hpp"
std::random_device rd;
std::mt19937 mt(rd());
int main() {
	rep(i, 15) {
		std::string file_name = "tests/in/random";
		file_name += (i < 10 ? "0" : "") + std::to_string(i);
		file_name += ".txt";
		FILE* f = freopen(file_name.c_str(), "w", stdout);
		int D = mt() % 100000 + 1, N = mt() % 100000 + 1;
		std::cout << D << '\n' << N << '\n';
		rep(i, N) {
			int L = mt() % D + 1, R = mt() % D + 1;
			if (L > R) std::swap(L, R);
			std::cout << L << ' ' << R << '\n';
		}
		fclose(f);
	}
	return 0;
}