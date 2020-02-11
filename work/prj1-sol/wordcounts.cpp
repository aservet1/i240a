#include<iostream>
#include<unordered_map>
#include<fstream>

static void
print_map(std::unordered_map<std::string,int> &map)
{
	for (auto it = map.cbegin(); it != map.cend(); ++it)
		std::cout << "{" << (*it).first << ": "
			<< (*it).second << "}" << std::endl;
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

std::unordered_map<std::string,int>
count_file_words(int max_n_out, int min_word_length, int max_word_length, std::string filename)
{
	std::unordered_map<std::string, int> wordcounts;
	std::ifstream inFile;
	std::string word;

	inFile.open(filename);
	if (!inFile) {
		std::cerr << "error opening file \"" << filename << "\"" << std::endl
			<< "exiting program" << std::endl;
		exit(1);
	}

	int word_length;
	int n_words_written = 0;
	while (inFile >> word) {
		word = fix_word(word);
		word_length = word.length();
		if (word_length >= min_word_length &&
		    word_length <= max_word_length &&
		    n_words_written <= max_n_out)
		{
			n_words_written += 1;
			wordcounts[word] += 1;
		}
	}

	return wordcounts;
}

int main(int argc, char *argv[])
{
	std::unordered_map wordcounts =
		count_file_words(10, 5, 5, "lab0.umt");

	print_map(wordcounts);
}
