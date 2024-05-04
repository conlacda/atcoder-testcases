#include <random>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class testcase {
public:
	int N, L, K;
	std::vector<int> A;
	std::vector<long long> C;
	testcase() : N(-1), L(-1), K(-1), A(std::vector<int>()), C(std::vector<long long>()) {};
	void print(std::ostream& os) const {
		os << N << ' ' << L << ' ' << K << '\n';
		for (int i = 0; i < N; i++) {
			os << A[i] << ' ' << C[i] << '\n';
		}
	}
};

class myrandom {
private:
	std::mt19937_64 mt;
public:
	myrandom() : mt(std::mt19937_64()) {};
	myrandom(std::uint64_t seed) : mt(std::mt19937_64(seed)) {};
	std::int64_t next_long(std::int64_t l, std::int64_t r) {
		return l + std::int64_t(mt() % (r - l));
	}
};

testcase gen_random(int N, int L, int K, std::uint64_t seed) {
	myrandom rd(seed);
	testcase T;
	T.N = N;
	T.L = L;
	T.K = K;
	T.A = std::vector<int>(T.N);
	T.C = std::vector<long long>(T.N);
	for (int i = 0; i < T.N; i++) {
		T.A[i] = rd.next_long(1, L - 1);
		T.C[i] = rd.next_long(1, 1'000'000'000'000);
	}
	std::sort(T.A.begin(), T.A.end());
	return T;
}

testcase gen_almost_monotone(int N, int L, int K, const std::string& mode, std::uint64_t seed) {
	myrandom rd(seed);
	testcase T;
	T.N = N;
	T.L = L;
	T.K = K;
	T.A = std::vector<int>(T.N);
	T.C = std::vector<long long>(T.N);
	for (int i = 0; i < T.N; i++) {
		T.A[i] = (long long)(i) * (L - 1) / N + 1;
		T.C[i] = rd.next_long(1, 1'000'000'000'000);
	}
	std::sort(T.A.begin(), T.A.end());
	if (mode == "increasing") {
		std::sort(T.C.begin(), T.C.end());
	}
	if (mode == "decreasing") {
		std::sort(T.C.begin(), T.C.end(), std::greater<long long>());
	}
	for (int i = 0; i < T.N; i++) {
		int pos = rd.next_long(0, T.N - 1);
		std::swap(T.C[pos], T.C[pos + 1]);
	}
	return T;
}

int main() {
	// subtask 1
	std::vector<testcase> sub1(3);
	sub1[0] = gen_random(98, 100, 5, 100159);
	sub1[1] = gen_random(99, 99, 16, 100265);
	sub1[2] = gen_random(100, 98, 47, 100309);

	// subtask 2
	std::vector<testcase> sub2(8);
	sub2[0] = gen_random(700000, 700000, 20, 200186);
	sub2[1] = gen_random(320000, 690000, 235, 200251);
	sub2[2] = gen_random(680000, 250000, 5601, 200344);
	sub2[3] = gen_random(699999, 699997, 65414, 200490);
	sub2[4] = gen_almost_monotone(699999, 700000, 3, "increasing", 200550);
	sub2[5] = gen_almost_monotone(699999, 700000, 350000, "increasing", 200658);
	sub2[6] = gen_almost_monotone(699999, 700000, 1, "decreasing", 200716);
	sub2[7] = gen_almost_monotone(699999, 700000, 234567, "decreasing", 200832);

	// output
	for (int i = 0; i < 3; i++) {
		std::ofstream fout("../in/sub1_0" + std::to_string(i + 1) + ".txt");
		sub1[i].print(fout);
	}
	for (int i = 0; i < 8; i++) {
		std::ofstream fout("../in/sub2_0" + std::to_string(i + 1) + ".txt");
		sub2[i].print(fout);
	}

	return 0;
}