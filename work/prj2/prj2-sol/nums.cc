#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include "arrayseq.hh"
#include "validate.hh"

using namespace std;
using TestType = int;

void readFileIntoSequence(string inFileName, Seq<TestType>* sequence)
{
	ifstream inFile;
	inFile.open(inFileName);
	if (!inFile) { cerr << "Unable to open " << inFileName << endl; exit(1); }
	int i;
	while (inFile >> i) {
		sequence->push(i);
		//cout << i << " ";
	} //cout << endl;

}

void printSequence(Seq<TestType>* seq)
{
  ConstIterPtr<TestType> startPointer = seq->cbegin();
	ConstIterPtr<TestType> endPointer = seq->cend();
	ConstIter<TestType>& a = *startPointer;
	ConstIter<TestType>& b = *endPointer;
  //*iterP accessed iterator wrapped by smart-pointer iterP
  while (a || b)
	{
    cout << *a << endl;
		cout << *b << endl;
		++a; --b;
  }
}

// ./seq-test [-a] inputfile.data
int main(int argc, char *argv[])
{
	auto args = vector<string>(&argv[1], &argv[argc]);
	validate_cmd_args(args);
	string inFileName;
	if (args[0] == "-a") {
		string option = args[0]; // make this a bool for arr/dlink later on
		inFileName = args[1];
	}
	else inFileName = args[0];

	SeqPtr<TestType> smartPointer = ArraySeq<TestType>::make(); //this should prolly have a different name than smartPointer
	Seq<TestType>* ptr = smartPointer.get();

	readFileIntoSequence(inFileName, ptr);
	printSequence(ptr);

	return 0;
}
