#include "languagemodel.h"
#include "relative_frequencies.h"
#include <iostream>
#include <map>

int main(int argc, char *argv[])
{
    LanguageModel w("ovis-trainset.txt");
    Relative_frequencies f("ovis-trainset.txt");
    //for (auto &pair : w.bigram_counts) {
    //   std::cout << pair.first << ": " << pair.second << std::endl;
    //}

    for (auto &pair : f.corpus) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}
