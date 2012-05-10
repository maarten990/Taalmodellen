#include "relative_frequencies.h"
#include <iostream>
#include <fstream>

using namespace std;

Relative_frequencies::Relative_frequencies(string corpus_path)
{
    Relative_frequencies::Relative_frequencies(corpus_path.c_str());
}

Relative_frequencies::Relative_frequencies(const char corpus_path[])
{
    // load in corpus
    ifstream file(corpus_path);
    string line;

    // while file is good
    while (file.good()) {
        getline(file, line);

        //alphabet = "abc...z"
        //if (alphabet.find(jouw_string) != alphabet.end())
            // het is een letter
        // increment all lettes per line in the corpus map
       for (auto letter = line.begin(); letter != line.end(); ++ letter)
       {
           if();
       }
    }
}



LanguageModel::LanguageModel(const char corpus_path[])
{
    ifstream file(corpus_path);
    string line;

    while (file.good()) {
        getline(file, line);

        // for each letter we increase its count
        for (auto letter = line.begin(); letter != line.end(); ++letter) {
            unigram_counts[string(1, *letter)] += 1;
            bigram_counts[string(letter-1, letter+1)] += 1;
        }
    }
}
