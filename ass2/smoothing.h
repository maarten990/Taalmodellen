#ifndef SMOOTHING_H
#define SMOOTHING_H

#include <vector>
#include <string>
#include <fstream>
#include <boost/regex.hpp>
#include <iostream>

#include "ngram_requency.h"
#include "probabilities.h"

#include <assert.h>
#include <math.h>

map<int, int> nc_construct(map<string, int> &nmap, int unaries_size);
void gt_smoothing(map<string, int> nmap, int n,int size_unaries);
void simple_gt(map<int, int> &Ncs);
void ensure_nonzero(double *c, const map<int, int> &ncs);
double smoothed_probability(vector<string> ngram,
                            const map<string, int> &ngram_freqs,
                            const map<int, int> &freq_freqs);
double smoothed_sentence_probability(const vector<string> &words, int n,
                                     map<string, int> &nfreqs,
                                     const map<string, int> &unaries);
double get_c_star(vector<string> ngram,
                  const map<string, int> &ngram_freqs,
                  map<int, int> &freq_freqs);

void print_all_sentence_probs(char *file_path, int n, 
                              map<string, int> &nfreqs,
                              map<string, int> &unaries);

#endif // PROBABILITIES_H
