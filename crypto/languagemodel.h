#ifndef WORDMODEL_H
#define WORDMODEL_H

#include <string>
#include <map>

using namespace std;

/*
 * constructs a unigram and bigram letter-model over a given training corpus
 */
class LanguageModel
{
public:
    // overloaded constructors
    LanguageModel(string corpus_path);
    LanguageModel(const char corpus_path[]);

    map<string, int> bigram_counts;
    map<string, int> unigram_counts;
};

#endif
