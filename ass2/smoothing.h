#ifndef SMOOTHING_H
#define SMOOTHING_H

#include <vector>
#include <string>
#include <fstream>
#include <boost/regex.hpp>
#include <iostream>

#include "ngram_requency.h"

#include <assert.h>
#include <math.h>

map<int, double> nc_construct(map<string, int> &nmap, int unaries_size);
void gt_smoothing(map<string, int> nmap, int n,int size_unaries);
void simple_gt(map<int, double> &Ncs);

#endif // PROBABILITIES_H
