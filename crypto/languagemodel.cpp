#include "languagemodel.h"
#include <iostream>
#include <fstream>

using namespace std;

LanguageModel::LanguageModel(string corpus_path)
{
    // delegate it to the char* constructor
    LanguageModel(corpus_path.c_str());
}

LanguageModel::LanguageModel(const char corpus_path[])
{
    ifstream file(corpus_path);
    string line;

    while (file.good()) {
        getline(file, line);

        // for each letter
        for (auto letter = line.begin(); letter != line.end(); ++letter) {
            unigram_counts[string(1, *letter)] += 1;

            // special case for the first letter and the bigram model
            if (letter == line.begin())
                bigram_counts["<s>" + string(1, *letter)] += 1;
            else
                bigram_counts[string(letter-1, letter+1)] += 1;
        }
    }
}
