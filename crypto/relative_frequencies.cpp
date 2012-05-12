#include "relative_frequencies.h"

Relative_frequencies::Relative_frequencies(string corpus_path)
{
    Relative_frequencies(corpus_path.c_str());
}

Relative_frequencies::Relative_frequencies(const char corpus_path[])
{
    // load in corpus
    ifstream file(corpus_path);
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
                corpus[string(1, *letter)] += 1;
                // increment totalcount
                total_count_N += 1;
            }
       }

    }
    // we use function relative_frequency to set all letters to their relative
    // frequency. All not occuring letters are set to 0.
    relative_frequency(total_count_N);
}

// Relative frequency introduces the relative count to the absolute count
void Relative_frequencies::relative_frequency(int N){

    string alfabet = "abcdefghijklmnopqrstuvwxyz";
    // For all letters in the alfabet
    for ( auto letter = alfabet.begin(); letter != alfabet.end(); ++letter)
    {
        // If the letter is already in the map
        if(corpus.find(string(1, *letter)) != corpus.end())
        {
            // Normalize the frequency
            corpus[string(1, *letter)] /= N;
        }
        else{
            // Else put the key in the map with value zero
            corpus[string(1, *letter)] = 0;
        }
    }

}


