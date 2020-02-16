#include<iostream>
#include<unordered_map>
#include<fstream>
#include<vector>
#include<algorithm>

static void
print_map(std::unordered_map<std::string,int> &map)
{
	for (auto it = map.cbegin(); it != map.cend(); ++it)
		std::cout << (*it).first << ": "
			<< (*it).second << std::endl;
}

static std::string
fix_word(std::string inWord)
{
	std::string outWord;
	for (char c : inWord)
		if (isalpha(c))
			outWord += tolower(c);
	return outWord;
}

static std::ifstream
open_file_check_error(std::string fileName)
{
	std::ifstream inFile;
	inFile.open(fileName);
	if (!inFile) {
		std::cerr << "error opening file \"" << fileName << "\"" << std::endl
			<< "exiting program" << std::endl;
		exit(1);
	}
	return inFile;
}

/*bool is_in(std::string key, std::vector<std::string> vect)
{
	for (unsigned long i = 0; i < vect.size(); i++)
		if(vect[i] == key) return true;
	return false;
}*/

static bool is_int_string(std::string s)
{
	for (char c : s) if (!isdigit(c)) return false;
	return true;
}

static bool wordCompare()
{
	return false;
}

static std::unordered_map<std::string,int>
count_file_words(/*int max_n_out,*/
		 int min_word_length,
		 int max_word_length,
		 std::string fileName)
{
	std::unordered_map<std::string, int> wordcounts;

	std::ifstream inFile = open_file_check_error(fileName);

	std::string word;
	int word_length;
	std::vector<std::string> words_written;
	while (inFile >> word) {
		word = fix_word(word);
		word_length = word.length();
		if (word_length >= min_word_length
		 && word_length <= max_word_length)
		{
	//		if (is_in(word,words_written))
				wordcounts[word] += 1;
	//		else {
	//			if ((int)words_written.size() < max_n_out) {
	//				words_written.push_back(word);
	//				wordcounts[word] += 1;
	//			}
	//		}
		}
	}
	inFile.close();
	return wordcounts;
}

int main(int argc, char *argv[])
{
	if (argc < 5) {
		std::cerr << "usage: ./worcounts MAX_N_OUT MIN_WORD_LEN MAX_WORD_LEN FILE..." << std::endl;
		exit(1);
	}

	for(int i = 1; i < 4; i++) {
		if (!is_int_string(argv[i])) {
			std::cerr << "Bad integer value \"" << argv[i] << "\"" << std::endl;
			exit(1);
		} //@TODO -- 'for MAX_WORD_LEN' with an enum or something
	}

	int max_n_out = std::stoi(argv[1]);
	int min_word_len = std::stoi(argv[2]);
	int max_word_len = std::stoi(argv[3]);

	std::unordered_map wordcounts =
		count_file_words(/*max_n_out,*/ min_word_len, max_word_len, argv[4]);
		//@TODO -- make this handle multi file input
	print_map(wordcounts);
}
