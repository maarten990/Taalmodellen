#ifndef RELATIVE_FREQUENCIES_H
#define RELATIVE_FREQUENCIES_H
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Relative_frequencies
{
public:
    Relative_frequencies(std::string corpus_path, string cipher_path);
    Relative_frequencies(const char corpus_path[], const char cipher_path[]);

    // The maps used for relative frequency storage
    map<string, double> cipher;
    map<string, double> corpus;
    void letter_count(const char path[], map<string, double> &map_count);
    void relative_frequency(int N, map<string, double> &map_count);

    double compute_lettermapping(char letter_corpus, char letter_cipher);
    double compute_lettermapping(string letter_corpus, string letter_cipher);
};

#endif // RELATIVE_FREQUENCIES_H
