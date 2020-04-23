#ifndef DELIM_ENCODINGS_HH_
#define DELIM_ENCODINGS_HH_

#include <unordered_map>

using namespace std;

bool isValid(char c)
{
	switch (c) {
	case '(': case '[': case '<': case '{':
	case ')': case ']': case '>': case '}':
		return true;
	default:
		return false;
	}
}

bool isOpener(char c)
{
	switch (c) {
	case '(': case '[': case '<': case '{':
		return true;
	default:
		return false;
	}
}

bool isCloser(char c)
{
	switch (c) {
	case ')': case ']': case '>': case '}':
		return true;
	default:
		return false;
	}
}

char getComplement(char c)
{
	unordered_map<char,char> complements;
	complements['('] = ')';
	complements['['] = ']';
	complements['<'] = '>';
	complements['{'] = '}';
	complements['}'] = '{';
	complements['>'] = '<';
	complements[']'] = '[';
	complements[')'] = '(';
	return complements[c];
}

#endif //ifndef DELIM_ENCODINGS_HH_
