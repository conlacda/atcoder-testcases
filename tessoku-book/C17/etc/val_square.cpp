#include <string>
#include <vector>
#include <iostream>
#include "testlib.h"

int main() {
	registerValidation();
	int Q = inf.readInt(2, 300000); inf.readChar('\n');
	int population = 0;
	bool query_d_exists = false;
	for (int i = 0; i < Q; i++) {
		char query_type = inf.readChar();
		ensure(query_type == 'A' || query_type == 'B' || query_type == 'C' || query_type == 'D');
		if (query_type == 'A' || query_type == 'B') {
			inf.readChar(' ');
			std::string str;
			while (true) {
				char ch = inf.readChar();
				if (ch == '\n') {
					break;
				}
				str += ch;
			}
			ensure(std::size_t(1) <= str.size() && str.size() <= std::size_t(10));
			population += 1;
		}
		if (query_type == 'C' || query_type == 'D') {
			inf.readChar('\n');
			ensure(population >= 1);
			if (query_type == 'C') {
				population -= 1;
			}
			if (query_type == 'D') {
				query_d_exists = true;
			}
		}
	}
	inf.readEof();
	ensure(query_d_exists);
	return 0;
}