#include "languagemodel.h"
#include "relative_frequencies.h"
#include <iostream>
#include <map>
#include <cmath>
#include <string>
#include <iostream>

//write the file to lowercase
void file_to_lowercase(string pathname, bool corpus){
    ifstream file(pathname.c_str());

    ofstream newfile;

    string line;


    if(corpus == true)
    {
        newfile.open("corpus.txt");
    }
    else{
        newfile.open("cipher.txt");
    }
    // while file is good
    while (file.good()) {
        getline(file, line);

        // increment all lettes per line in the corpus map
       for (auto letter = line.begin(); letter != line.end(); ++ letter)
       {
            // given the iterator points at a letter
            if (isalpha(int(*letter)))
            {
                *letter =(char)tolower(*letter);
            }
       }
       newfile << line;

    }
    newfile.close();
}


int main(int argc, char *argv[])
{


    if(argc != 3)
    {
        std::cout<<"Correct usage: ./cryptografie corpus-path cipher-path"
                <<std::endl;

    }


    // The two files are first stripped from possible uppercases
    file_to_lowercase(argv[1], true);
    file_to_lowercase(argv[2], false);

    // Construct the relative frequencies
    Relative_frequencies f("corpus.txt" , "cipher.txt");
    for (auto &pair : f.corpus) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    for (auto &pair : f.cipher) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }


    for (auto &pair : f.corpus) {
        for (auto &pair2 : f.cipher) {
            std::cout<<pair.first<<" "<< pair2.first<< ": "<<
                       1 - abs(pair.second-pair2.second)<<std::endl;
        }
    }


}
