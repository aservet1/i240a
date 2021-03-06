#include<iostream>
#include<unordered_map>
#include<fstream>
#include<vector>
#include<algorithm>

typedef std::pair<std::string,int> WordCount;
typedef std::unordered_map<std::string,int> WordMap;

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

static bool
is_int_string(std::string s)
{
	for (char c : s) if (!isdigit(c)) return false;
	return true;
}

static bool
wordCompare(WordCount wc1, WordCount wc2)
{
	if (wc1.second == wc2.second)
		return wc1.first < wc2.first;
	else return wc1.second > wc2.second;
}

static WordMap
count_file_words(int min_word_length, int max_word_length, std::vector<std::string> fileNames)
{
	WordMap wordcounts;
	for (std::string fileName : fileNames)
	{
		std::ifstream inFile = open_file_check_error(fileName);

		std::string word;
		int word_length;
		while (inFile >> word) {
			word = fix_word(word);
			word_length = word.length();
			if (word_length >= min_word_length && word_length <= max_word_length)
					wordcounts[word] += 1;
		}
		if (!inFile.eof()) {
			std::cerr << "error: reading file \"" <<
			fileName << "\" didn't reach eof before closing" << std::endl;
			exit(1);
		}
		inFile.close();
	}
	return wordcounts;
}

std::vector<WordCount>
sort_map(WordMap map)
{
	std::vector<WordCount> mapvector = std::vector<WordCount>(map.begin(),map.end());
	std::sort (mapvector.begin(), mapvector.end(), wordCompare);
	return mapvector;
}

void words_out(int max_n_out, std::vector<WordCount> sortedWords)
{
	for (long unsigned int i = 0; i < (long unsigned int)max_n_out && i < sortedWords.size(); i++)
		std::cout << sortedWords[i].first << ": " << sortedWords[i].second << std::endl;
}

int
main(int argc, char *argv[])
{
	if (argc < 5) {
		std::cerr << "usage: ./worcounts MAX_N_OUT MIN_WORD_LEN MAX_WORD_LEN FILE..." << std::endl;
		exit(1);
	}

	bool found_bad_int_val = false;
	for(int i = 1; i < 4; i++) {
		if (!is_int_string(argv[i])) {
			found_bad_int_val = true;
			std::string arg_name;
			switch (i) {
				case 1: arg_name = "MAX_N_OUT";    break;
				case 2: arg_name = "MIN_WORD_LEN"; break;
				case 3: arg_name = "MAX_WORD_LEN"; break;
			}
			std::cerr << "Bad integer value \"" << argv[i] << "\" for " << arg_name << std::endl;
		}
	} if (found_bad_int_val) exit(1);

	int max_n_out = std::stoi(argv[1]);
	int min_word_len = std::stoi(argv[2]);
	int max_word_len = std::stoi(argv[3]);

	if (min_word_len > max_word_len) {
		std::cerr << "MIN_WORD_LEN " << min_word_len << " is greater than MAX_WORD_LEN " << max_word_len << std::endl;
	}

	std::vector<std::string> fileNames = std::vector<std::string>(&argv[4],&argv[argc]);
	std::unordered_map wordcounts = count_file_words(min_word_len, max_word_len, fileNames);
	std::vector<WordCount> sortedWords = sort_map(wordcounts);
	words_out(max_n_out,sortedWords);

	return 0;
}
