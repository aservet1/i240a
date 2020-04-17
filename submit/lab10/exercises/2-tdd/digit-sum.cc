#include <cctype>

#include "digit-sum.hh"

#define to_digit(n) n - '0'

int
valid_char(char c)
{
	return (isspace(c)) || (isdigit(c)) || (c == '+');
}

int
digitSum(const char* str)
{
	int acc = 0;
	bool wantDigit = true;
	for (const char* p = str; (*p != 0 && valid_char(*p)); ++p) {
		int c = *p;
		if (isspace(c))
			continue;
		if (isdigit(c)) {
			if (wantDigit) {
				acc += to_digit(c);
				wantDigit = false;
			} else {
				break;
			}
		} else if (c == '+') {
			if (wantDigit)
				break;
			else
				wantDigit = true;
		} else {
			break;
		}
	}
	return acc;
}
