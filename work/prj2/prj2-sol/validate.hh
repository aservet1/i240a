using namespace std;

static void invalid_usage_abort()
{
	cerr << "usage: ./seq-test [-a] filename" << endl;
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
