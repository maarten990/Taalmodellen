#ifndef WORDMODEL_H
#define WORDMODEL_H

#include <string>
#include <map>
#include <vector>

using namespace std;

/*
 * constructs a unigram and bigram letter-model over a given training corpus
 */
class LanguageModel
{
public:
    /* methods */

    // overloaded constructors
    LanguageModel(string corpus_path);
    LanguageModel(const char corpus_path[]);

    // returns P(b | a) given the string "ab"
    double get_probability(string bigram);
    double get_probability(string a, string b);
    double get_probability(char a, char b);

    /* fields */

    // static alphabet vector containing each letter of the alphabet
    static vector<string> alphabet;

private:
    /* methods */

    // opens the file-path given in the first argument, and uses it to fill
    // the given maps with unigram and bigram letter-counts
    void initialize_counts(const char corpus_path[],
                           map<string, int> &unigram_counts,
                           map<string, int> &bigram_counts);
    /* fields */
    map<string, int> m_unicounts;
    map<string, int> m_bicounts;
};

#endif
