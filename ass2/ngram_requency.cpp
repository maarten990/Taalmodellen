#include "ngram_requency.h"

using namespace std;

/*
 * returns the frequency of each ngram from a given corpus
 */
map<string, int> ngram_frequencies(char file_location[], int n)
{
    // first we read the file into a vector of lines, and add the start- and endsymbols to each line
    vector<string> lines = get_lines(file_location);
    add_symbols(lines, n);

    // then we loop through each line to get the ngrams
    map<string, int> ngram_count;
    vector<string> words;
    for (string& line : lines) {

        // splitting the line into words by regex
        boost::regex re("\\s+");
        boost::sregex_token_iterator i(line.begin(), line.end(), re, -1);
        boost::sregex_token_iterator j;
        while (i != j) {
            words.push_back(*i++);
        }

        // in each sentence we will collect the n-grams
        string temp;
        for (int i = 0; i < words.size() - n + 1; ++i) {
            temp = "";
            for (int j = 0; j < n; ++j) {
                temp.append(words[i+j] + " ");
            }

            ngram_count[temp] += 1;
        }

        // clearing the words vector
        words.clear();
    }

    return ngram_count;
}

/*
 * reads each line of a file into a vector
 */
vector<string> get_lines(char file_location[])
{
    ifstream file(file_location);
    string line;
    vector<string> output;

    // while the file is good (that is, until EOF is reached or an error occurs)
    while (file.good()) {
        getline(file, line);
        output.push_back(line);
    }

    // cleaning up
    file.close();
    return output;
}

/*
 * adds start/end symbols to each line
 *
 * Warning: modifies input
 */
void add_symbols(vector<string> &lines, int n)
{
    // first we build the string containing n-1 <s> symbols to be prepended to each line
    string prefix = "";
    for (int i = 0; i < n-1; ++i) {
        prefix.append("<s> ");
    }

    // looping through each line
    for (int i = 0; i < lines.size(); ++i) {
        lines[i] = prefix + lines[i] + "<\\s> ";
    }
}

// sorting it
void map_sort(map<string, int> &counts){

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
}
