#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;
using TestType = int;

static void invalid_usage_abort()
{
	cerr << "usage: ./seq-test [-a] ArraySeq|DLinkSeq" << endl;
	exit(1);
}

static void validate_cmd_args(vector<string>& args)
{
	if (args.size() == 0) {
		invalid_usage_abort();
	}
	else if (args.size() == 1) {
//		if (args[0] != "ArraySeq" && args[0] != "DLinkSeq")
//			invalid_usage_abort();
	}
	else if (args.size() == 2) {
		if (args[0] != "-a")
			invalid_usage_abort();
//		if (args[1] != "ArraySeq" && args[1] != "DLinkSeq")
//			invalid_usage_abort();
	}
	else if (args.size() > 2) {
			invalid_usage_abort();
	}
}

void readFileInts(string inFileName)
{
	ifstream inFile;
	inFile.open(inFileName);
	if (!inFile) {
		cerr << "Unable to open " << inFileName << endl;
		exit(1);
	}
	int i;
	while (inFile >> i) {
		cout << i << " ";
	} cout << endl;

}


// ./seq-test [-a] inputfile.txt
int main(int argc, char *argv[])
{
	auto args = vector<string>(&argv[1], &argv[argc]);
	validate_cmd_args(args);
	string inFileName;
	if (args[0] == "-a") {
		string option = args[0];
		inFileName = args[1];
	}
	else inFileName = args[0];

	readFileInts(inFileName);

	return 0;
}
