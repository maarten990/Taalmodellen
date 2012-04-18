#ifndef NGRAM_REQUENCY_H
#define NGRAM_REQUENCY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <boost/regex.hpp>

using namespace std;

// function declarations
map<string, int> ngram_frequencies(char file_location[], int n);
vector<string> get_lines(char file_location[]);
void add_symbols(vector<string> &lines, int n);
void map_sort(map<string, int> &counts);

#endif // NGRAM_REQUENCY_H
