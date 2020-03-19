#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include "arrayseq.hh"
#include "dlinkseq.hh"
#include "validate.hh"

using namespace std;
using TestType = int;

void readFileIntoSequence(string inFileName, Seq<TestType>* sequence)
{
	ifstream inFile; inFile.open(inFileName);
	if (!inFile) { cerr << "Unable to open " << inFileName << endl; exit(1); }
	int i;
	while (inFile >> i) {
		sequence->push(i);
	}
}

void printSequence(Seq<TestType>* seqPtr)
{
  ConstIterPtr<TestType> startPointer = seqPtr->cbegin();
	ConstIterPtr<TestType> endPointer = seqPtr->cend();
	ConstIter<TestType>& a = *startPointer;
	ConstIter<TestType>& b = *endPointer;
  while (a || b) {
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

	SeqPtr<TestType> smartPointer = DLinkSeq<TestType>::make(); //this should prolly have a different name than smartPointer
	Seq<TestType>* seqPtr = smartPointer.get();

	readFileIntoSequence(inFileName, seqPtr);
	cout << *seqPtr << endl;
	printSequence(seqPtr);

	return 0;
}
