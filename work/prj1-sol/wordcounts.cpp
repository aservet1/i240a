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

std::ifstream
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

bool is_in(std::string key, std::vector<std::string> vect)
{
	for (unsigned long i = 0; i < vect.size(); i++)
		if(vect[i] == key) return true;
	return false;
}

bool wordCompare()
{
	return false;
}

std::unordered_map<std::string,int>
count_file_words(int max_n_out,
		 int min_word_length,
		 int max_word_length,
		 std::string fileName)
{
	std::unordered_map<std::string, int> wordcounts;
	std::string word;

	std::ifstream inFile = open_file_check_error(fileName);

	int word_length;
	std::vector<std::string> words_written;
	while (inFile >> word) {
		word = fix_word(word);
		word_length = word.length();
		if (word_length >= min_word_length
		 && word_length <= max_word_length)
		{
			if (is_in(word,words_written))
				wordcounts[word] += 1;
			else {
				if ((int)words_written.size() < max_n_out) {
					words_written.push_back(word);
					wordcounts[word] += 1;
				}
			}
		}
	}
	inFile.close();
	return wordcounts;
}

int main(int argc, char *argv[])
{
	std::unordered_map wordcounts =
		count_file_words(10, 5, 6, "lab0.umt");

	print_map(wordcounts);
}
