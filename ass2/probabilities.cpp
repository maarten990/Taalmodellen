#include "probabilities.h"

using namespace std;

vector<string> parse_sentences(char file_path[], int n)
{
    ifstream file(file_path);

    string line;
    vector<string> words;
    while (file.good()) {
        // getting each line into a file of words
        getline(file, line);
        words = split_line(line);

    }
}

vector<string> split_line(string line)
{
    boost::regex re("\\s+");
    boost::sregex_token_iterator i(line.begin(), line.end(), re, -1);
    boost::sregex_token_iterator j;
    while (i != j) {
        words.push_back(*i++);
    }
}
