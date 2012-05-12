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

private:
    /* methods */

    // opens the file-path given in the first argument, and uses it to fill
    // the given maps with unigram and bigram letter-counts
    void initialize_counts(const char corpus_path[],
                           map<string, int> &unigram_counts,
                           map<string, int> &bigram_counts);
    /* fields */
    map<string, double> m_uni_relcount;
    map<string, double> m_bi_relcount;
};

#endif
