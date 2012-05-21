#include "relative_frequencies.h"
#include <math.h>
#include <algorithm>

#include <iostream>
using namespace std;

Relative_frequencies::Relative_frequencies(string corpus_path, string cipher_path)
{
    Relative_frequencies(corpus_path.c_str(), cipher_path.c_str());
}

Relative_frequencies::Relative_frequencies(const char corpus_path[], const char cipher_path[])
{
        letter_count(corpus_path, corpus);
        letter_count(cipher_path, cipher);

        // constructing the rankings
        for (auto &p : corpus)
            m_corpus_rank.push_back(p.first);
        for (auto &p : cipher)
            m_cipher_rank.push_back(p.first);

        // now we sort them based on their frequency in reverse order (high to
        // low)
        sort(m_corpus_rank.begin(), m_corpus_rank.end(),
                [this](string a, string b)->bool { return corpus[a] > corpus[b]; });

        sort(m_cipher_rank.begin(), m_cipher_rank.end(),
                [this](string a, string b)->bool { return cipher[a] > cipher[b]; });
}

void Relative_frequencies::letter_count(const char path[], map<string, double> &map_count){
    // load in corpus
    ifstream file(path);
    string line;

    // Total count of all letter in the file
    int total_count_N = 0;

    // string with all letters in the alphabet
    string alphabet = "abcdefghijklmnopqrstuvwxyz ";

    // while file is good
    while (file.good()) {
        getline(file, line);

        // increment all lettes per line in the corpus map
       for (auto letter = line.begin(); letter != line.end(); ++ letter)
       {
            // given the iterator points at a letter
            if (alphabet.find(string(1,*letter)) != string::npos)
            {
                // add 1 to the correct cipher map
                map_count[string(1, *letter)] += 1;
                // increment totalcount
                total_count_N += 1;
            }
       }

    }
    // we use function relative_frequency to set all letters to their relative
    // frequency. All not occuring letters are set to 0.
    relative_frequency(total_count_N, map_count);
}


// Relative frequency introduces the relative count to the absolute count
void Relative_frequencies::relative_frequency(int N, map<string, double> &map_count){

    string alfabet = "abcdefghijklmnopqrstuvwxyz";
    // For all letters in the alfabet
    for ( auto letter = alfabet.begin(); letter != alfabet.end(); ++letter)
    {
        // If the letter is already in the map
        if(map_count.find(string(1, *letter)) != corpus.end())
        {
            // Normalize the frequency
            map_count[string(1, *letter)] /= N;
        }
        else{
            // Else put the key in the map with value zero
            map_count[string(1, *letter)] = 0;
        }
    }
}

double Relative_frequencies::compute_lettermapping(const char letter_corpus,
                                                   const char letter_cipher)
{
    return compute_lettermapping(string(1, letter_corpus),
                                 string(1, letter_cipher));
}

// Returns the probability of a mapping given two letters
double Relative_frequencies::compute_lettermapping(string letter_corpus,
                                                   string letter_cipher)
{
    double dist = 1 - distance(letter_corpus, letter_cipher);
    double total_dist = 0;
    string alphabet = "abcdefghijklmnopqrstuvwxyz ";

    // calculating the sum of the emission frequencies
    for (char &letter : alphabet) {
        total_dist += 1 - distance(letter_corpus, string(1, letter));
    }

    //cout << "Dist, totaldist: " << dist << ", " << total_dist << endl;
    //cout << "dist/totaldist: " << dist/total_dist << endl;

    return dist / total_dist;
}

double Relative_frequencies::distance(string letter_corpus, string letter_cipher)
{
    // first we find the rank of the hidden state's letter
    int corp_rank;
    for (int i = 0; i < m_corpus_rank.size(); ++i)
        if (m_corpus_rank[i] == letter_corpus) {
            corp_rank = i;
            break;
        }
        
    // next we find the rank of the emission
    int cipher_rank;
    for (int i = 0; i < m_cipher_rank.size(); ++i)
        if (m_cipher_rank[i] == letter_cipher) {
            cipher_rank = i;
            break;
        }
        
    return abs(corp_rank - cipher_rank);
}
