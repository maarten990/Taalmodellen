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

struct Point
{
    double x;
    double y;
    
    Point(double x_val, double y_val)
    {
        x = x_val;
        y = y_val;
    }
};

map<int, int> nc_construct(map<string, int> &nmap, int unaries_size);
void gt_smoothing(map<string, int> nmap, int n,int size_unaries);
void simple_gt(map<int, int> &Ncs);
double interpolate(int x);
void ensure_nonzero(int c, double *nc, const map<int, int> &ncs);
double smoothed_probability(vector<string> ngram,
                            const map<string, int> &ngram_freqs,
                            vector<string> &keys,
                            const map<int, int> &freq_freqs);
double smoothed_sentence_probability(const vector<string> &words, int n,
                                     map<string, int> &nfreqs,
                                     const map<string, int> &unaries,
                                     vector<string> keys,
                                     bool katz=false);
double get_c_star(vector<string> ngram,
                  const map<string, int> &ngram_freqs,
                  map<int, int> &freq_freqs);

double smoothed_probability_backoff(vector<string> ngram,
                            const map<string, int> &ngram_freqs,
                            const map<int, int> &freq_freqs, int k=5);

double get_c_star_backoff(vector<string> ngram,
                  const map<string, int> &ngram_freqs,
                  map<int, int> &freq_freqs, int k=5);

void print_all_sentence_probs(char *file_path, int n, 
                              map<string, int> &nfreqs,
                              map<string, int> &unaries,
                              bool katz=false);
vector<string> binary_search(vector<string> &n1gram,
                  vector<string> &nfreqs);

#endif // PROBABILITIES_H
