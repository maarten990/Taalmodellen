#include "languagemodel.h"
#include "relative_frequencies.h"
#include <iostream>
#include <map>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;

// viterbi declaration
string viterbi(string observations, LanguageModel &lang_model,
               Relative_frequencies &task_model);

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


// We make a map that consists of the top 5 mapping
// belonging to a letter in cipher
map<string, string> calculate_top_5(map<string, double> cipher, map<string, double> corpus)
{
    map<string, string> top_5;
    double temp;
    double top1 = 0, top2 = 0, top3 = 0, top4 = 0, top5 = 0;
    string top1c = "-",top2c = "-", top3c = "-",top4c = "-", top5c = "-";
    for(auto &element: cipher)
    {
        for(auto &element2: corpus)
        {
            temp = 1 - abs(element.second - element2.second);

            if(1 - abs(element.second - element2.second) > top1)
            {
                top5 = top4;
                top5c= top4c;
                top4 = top3;
                top4c= top3c;
                top3 = top2;
                top3c= top2c;
                top2 = top1;
                top2c= top1c;
                top1 = temp;
                top1c = element2.first;
            }
            else if(temp > top2 )
            {
                top5 = top4;
                top5c = top4c;
                top4 = top3;
                top4c = top3c;
                top3 = top2;
                top3c = top2c;
                top2 = temp;
                top2c = element2.first;
            }
            else if(temp > top3 )
            {
                top5 = top4;
                top5c = top4c;
                top4 = top3;
                top4c = top3c;
                top3 = temp;
                top3c = element2.first;
            }
            else if(temp > top4 )
            {
                top5 = top4;
                top5c = top4c;
                top4 = temp;
                top4c = element2.first;
            }
            else if(temp > top5 )
            {
                top5 = temp;
                top5c = element2.first;
            }
        }
        // Now that we have a top 5 we insert it
        // in our map at the right location
        top_5[element.first] = top1c + top2c + top3c + top4c + top5c;
        top1 = 0;
        top2 = 0;
        top3 = 0;
        top4 = 0;
        top5 = 0;
    }
    return top_5;

}


int main(int argc, char *argv[])
{


    if(argc != 3)
    {
        std::cout<<"Correct usage: ./cryptografie corpus-path cipher-path"
                <<std::endl;
    }

    // The two files are first stripped from possible uppercases
    //file_to_lowercase(argv[1], true);
    //file_to_lowercase(argv[2], false);

    // Construct the task- and languagemodels
    Relative_frequencies t("corpus.txt" , "cipher.txt");
    LanguageModel l("corpus.txt");

    // reading the cipher text
    ifstream ifstr("cipher.txt");
    string str((istreambuf_iterator<char>(ifstr)),
               istreambuf_iterator<char>());
    ifstr.close();

    std::string s = viterbi(str, l, t);
    std::cout << "Most likely translation: " << s << std::endl;
}
