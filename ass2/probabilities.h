#ifndef PROBABILITIES_H
#define PROBABILITIES_H

#include <vector>
#include <string>
#include <fstream>
#include <boost/regex.hpp>
#include <iostream>

#include "ngram_requency.h"

using namespace std;

string nmap_to_string(vector<string> words);
void get_last_nmap(vector<string>&, int n);
vector<string> parse_sentences(char file_path[], int n);
vector<string> split_line(string line);
void add_symbols_sentence(vector<string> &sentence, int n);
void calculate_probability(vector<string> nmaps, int n,
                           map<string, int> n_frq, map <string, int> n1_freq );

#endif // PROBABILITIES_H
