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
{
    sentence.pop_back();
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
                           map<string, int> n_frq, map <string, int> n1_freq ){
    double w;
    double w2;
    double w3;
    vector<string> temp;
    string n1;
    for (int i = 0; i < nmaps.size(); i++){
        cout<< " Probability of sentence " << nmaps[i] << ": ";
        w = n_frq[nmaps[i]];
        temp = split_line(nmaps[i]);
        temp.pop_back();
        n1 = nmap_to_string(temp);
        w2 = n1_freq[n1];
        w3 = w/w2;
        cout<< w3 << endl;
        cout<< "w :" << w <<endl;
        cout<< "w2 :" << w2 <<endl;
        cout << "sentence one: " << nmaps[i] << endl;
        cout << "sentence two: " << n1 <<endl;
        n1 = "";
        w = 0;
        w2 = 0;

   }


}
