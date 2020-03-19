#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include "arrayseq.hh"
#include "dlinkseq.hh"
#include "validate_args.hh"

using namespace std;
using TestType = int;

void readFileIntoSequence(string inFileName, Seq<TestType>* seq)
{
	ifstream inFile; inFile.open(inFileName);
	if (!inFile) { cerr << "Unable to open " << inFileName << endl; exit(1); }
	TestType i;
	while (inFile >> i) {
		seq->push(i);
	}
}

void printSequence(Seq<TestType>* seq)
{
  ConstIterPtr<TestType> startPointer = seq->cbegin();
	ConstIterPtr<TestType> endPointer = seq->cend();
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
	bool useArrSeq = false;
	if (args.size() == 2) {
		useArrSeq = true;
		inFileName = args[1];
	} else {
		inFileName = args[0];
	}
	bool useDLinkSeq = !useArrSeq;

	SeqPtr<TestType> seqPointer;
	if(useArrSeq) seqPointer = ArraySeq<TestType>::make();
 	if(useDLinkSeq) seqPointer = DLinkSeq<TestType>::make();
	Seq<TestType>* rawPtr = seqPointer.get();

	readFileIntoSequence(inFileName, rawPtr);
	//cout << *seqPtr << endl;
	printSequence(rawPtr);

	return 0;
}
