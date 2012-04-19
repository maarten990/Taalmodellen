#include "ngram_requency.h"
#include "probabilities.h"
#include "smoothing.h"
#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 5) {
        cout << "Usage: ass2 n corpus sentences" << endl;
        exit(0);
    }

    // parsing arguments
    int n = atoi(argv[1]);
    char *corpus_path = argv[2];
    char *sentences_path = argv[3];

    // first we get the frequency maps of n-grams and (n-1)-grams
    map<string, int> unaries = ngram_frequencies(corpus_path, 1);
    map<string, int> n_freqs = ngram_frequencies(corpus_path, n);
    map<string, int> n1_freqs = ngram_frequencies(corpus_path, n-1);

    //print_all_sentence_probs(sentences_path, n, n_freqs, unaries);

    map<int, int> ncs  = nc_construct(n_freqs, unaries.size());
    simple_gt(ncs); // this readies the global variables

    print_all_sentence_probs(sentences_path, n, n_freqs, unaries);

    return 0;
}
