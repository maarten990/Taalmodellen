#include "ngram_requency.h"
#include "probabilities.h"
#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 5) {
        cout << "Usage: ass2 n corpus ngrams sentences" << endl;
        exit(0);
    }

    // parsing arguments
    int n = atoi(argv[1]);
    char *corpus_path = argv[2];
    char *ngrams_path = argv[3];
    char *sentences_path = argv[4];

    // first we get the frequency maps of n-grams and (n-1)-grams
    map<string, int> n_freqs = ngram_frequencies(corpus_path, n);
    map<string, int> n1_freqs = ngram_frequencies(corpus_path, n-1);

    // question 2
    //vector<string> nmaps = parse_sentences(ngrams_path, n);
    //calculate_probability(nmaps, n, n_freqs, n1_freqs);

    // question 3
    map<string, double> sentence_probs = parse_sentences_q3(sentences_path, n, n_freqs, n1_freqs);

    // printing the sentence probabilities
    for (auto& pair : sentence_probs) {
        cout << "Sentence: " << pair.first << endl;
        cout << "Probability: " << pair.second << endl << endl;
    }

    return 0;
}
