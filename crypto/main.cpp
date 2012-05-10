#include "wordmodel.h"
#include <iostream>
#include <map>

int main(int argc, char *argv[])
{
    LanguageModel w("ovis-trainset.txt");
    for (auto &pair : w.bigram_counts) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}
