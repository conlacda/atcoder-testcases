#include "../../../library/other/template.hpp"
std::random_device rd;
std::mt19937 mt(rd());
int main() {
	rep(i, 15) {
		std::string file_name = "tests/in/random";
		file_name += (i < 10 ? "0" : "") + std::to_string(i);
		file_name += ".txt";
		FILE* f = freopen(file_name.c_str(), "w", stdout);
		int N = mt() % 100000 + 1;
		std::cout << N << '\n';
		std::vector<int> A;
		rep(i, N) A.emplace_back(mt() & 1);
		std::cout << A << '\n';
		int Q = mt() % 100000 + 1;
		std::cout << Q << '\n';
		rep(i, Q) {
			int L = mt() % N + 1, R = mt() % N + 1;
			if (L > R) std::swap(L, R);
			std::cout << L << ' ' << R << '\n';
		}
		fclose(f);
	}
	return 0;
}