#include "languagemodel.h"
#include "relative_frequencies.h"
#include <iostream>
#include <map>

int main(int argc, char *argv[])
{


    if(argc != 3)
    {
        std::cout<<"Correct usage: ./cryptografie corpus-path cipher-path"
                <<std::endl;
    }

    // Construct the relative frequencies
    Relative_frequencies f(argv[1], argv[2]);
    for (auto &pair : f.corpus) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    for (auto &pair : f.cipher) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }


    for (auto &pair : f.corpus) {
        for (auto &pair : f.cipher) {
        }
    }


}
