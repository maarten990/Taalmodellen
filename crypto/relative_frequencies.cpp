#include "relative_frequencies.h"

Relative_frequencies::Relative_frequencies(string corpus_path, string cipher_path)
{
    Relative_frequencies(corpus_path.c_str(), cipher_path.c_str());
}

Relative_frequencies::Relative_frequencies(const char corpus_path[], const char cipher_path[])
{
        letter_count(corpus_path, corpus);
        letter_count(cipher_path, cipher);
}

void Relative_frequencies::letter_count(const char path[], map<string, double> &map_count){
    // load in corpus
    ifstream file(path);
    string line;

    // Total count of all letter in the file
    int total_count_N = 0;

    // string with all letters in the alphabet
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

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


