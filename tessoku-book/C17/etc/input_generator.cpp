#include <random>
#include <string>
#include <vector>
#include <fstream>

class testcase {
public:
	int Q;
	std::vector<std::string> queries;
	testcase() : Q(0), queries(std::vector<std::string>()) {};
	void print(std::ostream& os) {
		os << Q << '\n';
		for (int i = 0; i < Q; i++) {
			os << queries[i] << '\n';
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

std::string random_name(int len, myrandom& rd) {
	std::vector<std::string> tokens = {
		"a", "i", "u", "e", "o",
		"ka", "ki", "ku", "ke", "ko",
		"sa", "si", "su", "se", "so",
		"ta", "chi", "tsu", "te", "to",
		"na", "ni", "nu", "ne", "no",
		"ha", "hi", "fu", "he", "ho",
		"ma", "mi", "mu", "me", "mo",
		"ya", "yu", "yo",
		"ra", "ri", "ru", "re", "ro",
		"wa", "n",
		"ga", "gi", "gu", "ge", "go",
		"za", "ji", "zu", "ze", "zo",
		"da", "di", "du", "de", "do",
		"ba", "bi", "bu", "be", "bo",
		"pa", "pi", "pu", "pe", "po"
	};
	std::string res;
	while (true) {
		res = "";
		while (int(res.size()) < len) {
			res += tokens[rd.next_long(0, tokens.size())];
		}
		if (int(res.size()) == len) {
			break;
		}
	}
	return res;
}

testcase gen1(int Q, std::uint64_t seed) {
	myrandom rd(seed);
	testcase T;
	T.Q = Q;
	T.queries = std::vector<std::string>(Q);
	int level = 0;
	for (int i = 0; i < Q; i++) {
		int s;
		do {
			s = rd.next_long(0, 5);
		} while (level == 0 && s >= 2);
		if (s == 0) {
			T.queries[i] = "A " + random_name(rd.next_long(1, 11), rd);
			level += 1;
		}
		if (s == 1) {
			T.queries[i] = "B " + random_name(rd.next_long(1, 11), rd);
			level += 1;
		}
		if (s == 2 || s == 3) {
			T.queries[i] = "C";
			level -= 1;
		}
		if (s == 4) {
			T.queries[i] = "D";
		}
	}
	return T;
}

testcase gen2(int Q, std::uint64_t seed) {
	myrandom rd(seed);
	testcase T;
	T.Q = Q;
	T.queries = std::vector<std::string>(Q);
	int level = 0;
	for (int i = 0; i < Q; i++) {
		int s;
		do {
			s = rd.next_long(0, 7);
		} while (level == 0 && s >= 4);
		if (s == 0 || s == 1) {
			T.queries[i] = "A " + random_name(rd.next_long(1, 11), rd);
			level += 1;
		}
		if (s == 2 || s == 3) {
			T.queries[i] = "B " + random_name(rd.next_long(1, 11), rd);
			level += 1;
		}
		if (s == 4 || s == 5) {
			T.queries[i] = "C";
			level -= 1;
		}
		if (s == 6) {
			T.queries[i] = "D";
		}
	}
	return T;
}

testcase gen3(int Q, std::uint64_t seed) {
	myrandom rd(seed);
	testcase T;
	T.Q = Q;
	T.queries = std::vector<std::string>(Q);
	int level = 0;
	for (int i = 0; i < Q; i++) {
		int s;
		do {
			s = rd.next_long(0, 10);
		} while (level == 0 && s >= 4);
		if (s == 0 || s == 1) {
			T.queries[i] = "A " + random_name(rd.next_long(1, 11), rd);
			level += 1;
		}
		if (s == 2 || s == 3) {
			T.queries[i] = "B " + random_name(rd.next_long(1, 11), rd);
			level += 1;
		}
		if (s == 4 || s == 5 || s == 6 || s == 7 || s == 8) {
			T.queries[i] = "C";
			level -= 1;
		}
		if (s == 9) {
			T.queries[i] = "D";
		}
	}
	return T;
}

testcase gen4(int Q, std::uint64_t seed) {
	myrandom rd(seed);
	testcase T;
	T.Q = Q;
	T.queries = std::vector<std::string>(Q);
	int threshold = Q - Q / 5;
	for (int i = 0; i < threshold; i++) {
		int s = rd.next_long(0, 2);
		if (s == 0) {
			T.queries[i] = "A " + random_name(rd.next_long(1, 11), rd);
		}
		if (s == 1) {
			T.queries[i] = "B " + random_name(rd.next_long(1, 11), rd);
		}
	}
	for (int i = threshold; i < Q; i++) {
		int s = rd.next_long(0, 8);
		if (s <= 6) {
			T.queries[i] = "C";
		}
		if (s == 7) {
			T.queries[i] = "D";
		}
	}
	return T;
}

testcase gen5(int Q, std::uint64_t seed) {
	myrandom rd(seed);
	testcase T;
	T.Q = Q;
	T.queries = std::vector<std::string>(Q);
	int threshold = Q - Q / 5;
	for (int i = 0; i < threshold; i++) {
		T.queries[i] = "B " + random_name(rd.next_long(1, 11), rd);
	}
	for (int i = threshold; i < Q; i++) {
		int s = rd.next_long(0, 3);
		if (s == 0 || s == 1) {
			T.queries[i] = "C";
		}
		if (s == 2) {
			T.queries[i] = "D";
		}
	}
	return T;
}

testcase gen6(int Q, std::uint64_t seed) {
	myrandom rd(seed);
	testcase T;
	T.Q = Q;
	T.queries = std::vector<std::string>(Q);
	T.queries[0] = "B " + random_name(10, rd);
	for (int i = 1; i < Q; i++) {
		T.queries[i] = "D";
	}
	return T;
}

int main() {
	// testcase
	std::vector<testcase> T(6);
	T[0] = gen1(300000, 100140);
	T[1] = gen2(300000, 100258);
	T[2] = gen3(300000, 100361);
	T[3] = gen4(300000, 100417);
	T[4] = gen5(300000, 100589);
	T[5] = gen6(300000, 100602);

	// output
	for (int i = 0; i < 6; i++) {
		std::ofstream fout("../in/in0" + std::to_string(i + 1) + ".txt");
		T[i].print(fout);
	}

	return 0;
}