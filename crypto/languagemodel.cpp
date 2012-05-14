#include "languagemodel.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// the entire alphabet!
vector<string> LanguageModel::alphabet =
{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
 "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
 "u", "v", "w", "x", "y", "z"};

/*
 * constructors plus helper functions
 */
LanguageModel::LanguageModel(string corpus_path)
{
    // delegate it to the char[] constructor
    LanguageModel(corpus_path.c_str());
}

LanguageModel::LanguageModel(const char corpus_path[])
{
    // getting the counts
    initialize_counts(corpus_path, m_unicounts, m_bicounts);

    // making sure the unigram count contains each letter to avoid division by
    // zero errors
    for(string &letter : alphabet) {
        m_unicounts[letter] += 0;
    }
}

void LanguageModel::initialize_counts(const char corpus_path[],
                                      map<string, int> &unigram_counts,
                                      map<string, int> &bigram_counts)
{
    ifstream file(corpus_path);
    string line;

    // we iterate through each line in the corpus, and for each line the unigram
    // and bigram letter counts get saved in their respective maps
    while (file.good()) {
        getline(file, line);

        // for each letter we increase its count
        for (auto letter = line.begin(); letter != line.end(); ++letter) {
            unigram_counts[string(1, *letter)] += 1;

            if (letter != line.begin()) // safeguard for the first element
                bigram_counts[string(letter-1, letter+1)] += 1;
        }
    }
}

/*
 * the overloaded probability methods
 */
double LanguageModel::get_probability(char a, char b)
{
    return get_probability(string(1, a) + string(1, b));
}

double LanguageModel::get_probability(string a, string b)
{
    return get_probability(a + b);
}

double LanguageModel::get_probability(string bigram)
{
    string uni = string(1, bigram.at(0));
    return (m_unicounts[uni] > 0) ? (m_bicounts[bigram] / m_unicounts[uni]) : 0;
}
