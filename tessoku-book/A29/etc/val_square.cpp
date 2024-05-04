#include <set>
#include <iostream>
#include "testlib.h"

int main() {
	registerValidation();
	
	int A = inf.readInt(1, 100); inf.readChar(' ');
	int B = inf.readInt(1, 1000000000); inf.readChar('\n');
	inf.readEof();
	return 0;
}
