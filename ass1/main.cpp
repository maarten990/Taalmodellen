#include <iostream>
#include <cstdlib>
#include "ngram_requency.h"
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
    // checking for the right amount of arguments
    if (argc < 3) {
        cout << "Correct usage: ./main n file-location m" << endl;
        exit(0);
    }

    // extracting the arguments
    int n = atoi(argv[1]);
    char *file_location = argv[2];
    int m = atoi(argv[3]);

    // getting the frequency map
    map<string, int> counts = ngram_frequencies(file_location, n);

    // sorting it
    vector<string> keys;
    for (auto& i : counts) {
        keys.push_back(i.first);
    }

    sort(keys.begin(),
         keys.end(),
         [&counts](const string &a, const string &b) // lambda function!
         {
             return (counts[a] > counts[b]);
         });

    // print that shit
    for (int i = 0; i < m && i < keys.size(); ++i) {
        cout << keys[i] << ": " << counts[keys[i]] << endl;
    }
}
