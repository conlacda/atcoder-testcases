#include "../../../library/other/template.hpp"
std::random_device rd;
std::mt19937 mt(rd());
int main() {
	rep(i, 1) {
		std::string file_name = "tests/in/max";
		file_name += (i < 10 ? "0" : "") + std::to_string(i);
		file_name += ".txt";
		FILE* f = freopen(file_name.c_str(), "w", stdout);
		const int N = 100000, D = 100000;
		std::cout << N << '\n';
		std::vector<int> A(N);
		rep(i, N) A[i] = mt() % 100 + 1;
		std::cout << A << '\n' << D << '\n';
		rep(i, D) {
			int L = mt() % (N - 2) + 2, R = mt() % (N - 2) + 2;
			if (mt() & 1) L = mt() % 30 + 2, R = (N - 1) - mt() % 30;
			if (L > R) std::swap(L, R);
			std::cout << L << ' ' << R << '\n';
		}
		fclose(f);
	}
	return 0;
}