#include "languagemodel.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

LanguageModel::LanguageModel(string corpus_path)
{
    // delegate it to the char[] constructor
    LanguageModel(corpus_path.c_str());
}

LanguageModel::LanguageModel(const char corpus_path[])
{
    // getting the counts
    map<string, int> unigram_counts, bigram_counts;
    initialize_counts(corpus_path, unigram_counts, bigram_counts);

    // getting the total uni- and bigram counts
    int N_unigram = 0, N_bigram = 0;
    for_each(unigram_counts.begin(), unigram_counts.end(),
             [&N_unigram](pair<string, int> p) { N_unigram += p.second; });
    for_each(bigram_counts.begin(), bigram_counts.end(),
             [&N_bigram](pair<string, int> p) { N_bigram += p.second; });

    // converting counts to relative frequencies
    for (auto &p : unigram_counts)
        m_uni_relcount[p.first] = p.second / static_cast<double>(N_unigram);
    for (auto &p : bigram_counts)
        m_bi_relcount[p.first] = p.second / static_cast<double>(N_bigram);
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
