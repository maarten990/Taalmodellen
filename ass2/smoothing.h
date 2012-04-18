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
map<int, int> simple_gt(map<int, int> &Ncs);
void ensure_nonzero(double *c, const map<int, int> &ncs);
double smoothed_probability(vector<string> ngram,
                            const map<string, int> &ngram_freqs,
                            const map<int, int> &freq_freqs);

#endif // PROBABILITIES_H
