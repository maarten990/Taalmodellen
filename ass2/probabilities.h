#ifndef PROBABILITIES_H
#define PROBABILITIES_H

#include <vector>
#include <string>
#include <fstream>
#include <boost/regex.hpp>

using namespace std;

vector<string> parse_sentences(char file_path[], int n);
vector<string> split_line(string line);

#endif // PROBABILITIES_H
