#include "probabilities.h"

using namespace std;

vector<string> parse_sentences(char file_path[], int n)
{
    ifstream file(file_path);
    string line;
    vector<string> words;
    vector<string> all_last_nmaps;
    // counter for all_last_nmaps
    while (file.good()) {
        // getting each line into a file of words
        getline(file, line);
        words = split_line(line);
        if(words.size() != n){
            continue;
        }
        // at begin and end sentences
        //add_symbols_sentence(words,n);
        // retrieve last nmap from sentence
        //get_last_nmap(words, n);
        // store nmap as sentence in vector array
        all_last_nmaps.push_back(nmap_to_string(words));
    }

    return  all_last_nmaps;
}

// vector of strings becomes one string with spaces
string nmap_to_string(vector<string> words){
    string a = "";
    for(int i = 0; i < words.size(); i++)
    {
        a += words[i] + " ";
    }
    return a;
}

vector<string> split_line(string line)
{
    // will be returned
    vector<string> words;
    
    boost::regex re("\\s+");
    boost::sregex_token_iterator i(line.begin(), line.end(), re, -1);
    boost::sregex_token_iterator j;
    while (i != j) {
        words.push_back(*i++);
    }
    return words;
}

// finds the last nmap of the sentence (without <\s>)
void get_last_nmap(vector<string> &sentence, int n)
{ sentence.pop_back();
    // now remove all beginning elements until we keep last ngram
    while(sentence.size() != n)
    {
        sentence.erase(sentence.begin());
    }
}

// adds <s> to the sentences
void add_symbols_sentence(vector<string> &sentence, int n)
{
    for(int i = 0; i < n - 1; i ++)
    {
        sentence.insert(sentence.begin(), "<s>");
    }

    sentence.push_back("<\\s>");
}


void calculate_probability(vector<string> nmaps, int n,
                           map<string, int> &n_frq, map<string, int> &n1_freq ){
    double w;
    double w2;
    double w3;
    vector<string> temp;
    string n1;
    for (int i = 0; i < nmaps.size(); i++){
        cout<< " Probability of ngram " << nmaps[i] << ": ";
        w = n_frq[nmaps[i]];
        temp = split_line(nmaps[i]);
        temp.pop_back();
        n1 = nmap_to_string(temp);
        w2 = n1_freq[n1];
        w3 = w/w2;
        cout<< w3 << endl;
        n1 = "";
        w = 0;
        w2 = 0;

   }
}

/*
 * question 3
 */
map<string, double> parse_sentences_q3(char *sentences_path, int n,
                                  const map<string, int> &nfreqs,
                                  const map<string, int> &n1freqs)
{
    ifstream file(sentences_path);
    string line;
    vector<string> words;
    map<string, double> output;
    // counter for all_last_nmaps
    while (file.good()) {
        // getting each line into a vector of words
        getline(file, line);
        words = split_line(line);
        words.push_back("<\\s>");
        output[line] = sentence_probability(words, n, nfreqs, n1freqs);
    }

    return output;
}

/*
 * calculates the probability of a sentence occurring
 */
double sentence_probability(const vector<string> &words, int n,
                            const map<string, int> &nfreqs,
                            const map<string, int> &n1freqs)
{
    vector<string> substring;
    double probability = 1;
    int m = words.size();
    // outer "product" loop, looping through each n-gram in the sentence
    for (int i = 1; i <= m; ++i) {
        // inner loop for getting a substring of the sentence
        for (int j = i - n; j < i; ++j) {
            if (j < 0)
                substring.push_back("<s>");
            else
                substring.push_back(words[j]);
        }

        // multiplying the total with the probability of this n-gram
        probability *= ngram_probability(substring, nfreqs, n1freqs);
        substring.clear();
    }

    return probability;
}

/*
 * returns the probability of the last word given the previous words
 */
double ngram_probability(vector<string> ngram, const map<string, int> &nfreqs, const map<string, int> &n1freqs)
{
    // getting the n-1 gram
    vector<string> n1gram;
    for (auto i = ngram.begin(); i != (ngram.end() - 1); ++i) {
        n1gram.push_back(*i);
    }

    // getting the values from the maps
    auto n_iter = nfreqs.find(nmap_to_string(ngram));
    auto n1_iter = n1freqs.find(nmap_to_string(n1gram));

    // debug
    if (n1_iter == n1freqs.end()) {
        cout << nmap_to_string(n1gram) << endl;
    }

    // the strings have to exist in the maps
    assert(n_iter != nfreqs.end());
    assert(n1_iter != n1freqs.end());

    double freq_n = n_iter->second;
    double freq_n1 = n1_iter->second;

    return (freq_n / freq_n1);
}
