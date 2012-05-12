#ifndef RELATIVE_FREQUENCIES_H
#define RELATIVE_FREQUENCIES_H
#include <map>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Relative_frequencies
{
public:
    Relative_frequencies(std::string corpus_path);
    Relative_frequencies(const char corpus_path[]);

    // The maps used for relative frequency storage
    map<string, double> cipher;
    map<string, double> corpus;
    void relative_frequency(int N);
};

#endif // RELATIVE_FREQUENCIES_H
