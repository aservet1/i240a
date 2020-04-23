#include <iostream>
#include <unordered_map>
#include <cstring>
#include "stack.hh"

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

void exit_invalid(char c)
{
	cout << "invalid delimiter \'" << c << "\'" << endl;
	exit(1);
}

void exit_unbalanced(int i)
{
	cout << "unbalanced at argument " << i << endl;
	exit(1);
}

int main(int argc, char *argv[])
{
	Stack* s = new Stack();

	for (int i = 1; i < argc; i++)
	{
		if (strlen(argv[i]) != 1)
		{
			cout << "invalid arg: " << argv[i] << endl;
			cout << "only pass in chars" << endl;
		}
		char c = argv[i][0];
		if (!isValid(c))
		{
			exit_invalid(c);
		}
		if (isOpener(c))
		{
			s->push(c);
		}
		if (isCloser(c))
		{
			if (s->isEmpty() || s->pop() != getComplement(c))
			{
				exit_unbalanced(i);
			}
		}
	}
	if (!s->isEmpty())
	{
		exit_unbalanced(argc-1);
	}

	return 0;
}









