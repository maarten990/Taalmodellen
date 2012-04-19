#include "smoothing.h"

// calculating the Ncs
map<int, int> nc_construct(map<string, int> &nmap, int unaries_size){
    // Nc map;
    map<int, int> Ncs;
    vector<string> keys;
    for (auto& i : nmap) {
        keys.push_back(i.first);
    }

    sort(keys.begin(),
    keys.end(),
    [&nmap](const string &a, const string &b) // lambda function!
    {
        return (nmap[a] > nmap[b]);
    });

    cout << keys[0] << endl;
    cout << nmap[keys[0]] <<endl;
    int max_value = nmap[keys[0]];


    // Nc with c = 0 gets all the rest of the size
    Ncs[0] = (unaries_size * unaries_size) + 2*unaries_size - nmap.size();

    for(int c = 1 ; c < max_value + 1; c ++){
        Ncs[c] = 0;
        // incrementing Nc value
        for( auto &i: nmap){
            if(i.second == c){
                Ncs[c] +=1;
            }
        }
    }
    return Ncs;
}

// simple_gt gives smoothing to all values
void simple_gt(map<int, int> &Ncs){
    //now that we have filled the Ncs map we only need to change the 0 values
    int pointx;
    int pointy;
    // look for the smallest nonzero size
    for (int i = 0 ; i < Ncs.size(); i++){
        if(Ncs[i] != 0){
            pointx = Ncs[i];
            pointy = i;
            break;
        }
    }
    cout<< "Points!!!!" <<endl;
    cout<< Ncs.size()-1 << endl;
    cout << pointy << endl; // 0
    cout << Ncs[Ncs.size()-1] << endl;
    cout << pointx<<endl; //702358;
    
    
    int pointx2 =  Ncs[Ncs.size()-1];
    int pointy2 = Ncs.size()-1;
    //calculate a
    double a =(double)( log(pointy) - log(pointy2))/ (double)(log(pointx) - log(pointx2));
    //double a =  ((double)(log(Ncs.size()-1) - log(pointy))/(double)(log(Ncs[Ncs.size()-1]) - log(pointx)));
    cout << a << endl;
    
    // calculate b
    //double b = (double) pointy - a * pointx;
    //double b = log(pointy) - a * log(pointx); 
    double b = ((double)(log(pointx)*log(pointy2)-log(pointx2)*log(pointy)))/(double)((log(pointx)-log(pointy)));
    cout << b << endl;

    // calculate new values for Ncs
    for ( auto &i:Ncs){
        if(i.second == 0 ){
            Ncs[i.first] = exp(b) + pow(i.first, a);
            //Ncs[i.first] = exp(log(i.first) * a + b);
        }
    }
}

/*
 * returns the smoothed probability of an ngram
 *
 * parameters:
 * ngram - a vector of strings representing the ngram
 * ngram_freqs - a map of all known ngrams and their frequency
 * freq_freqs - a map of Nc, the amount of ngrams having a certain frequency
 */
double smoothed_probability(vector<string> ngram,
                            const map<string, int> &ngram_freqs,
                            map<int, int> &freq_freqs)
{
    
    // first we got the top part of the division
    double c_star = get_c_star(ngram, ngram_freqs, freq_freqs);
    // now we calculate the summation on the bottom of the division
    // slow, naive method
    double sum = 0;
    vector<string> tokens, wn1;
    string tokens_head;
    for (auto& key_val : ngram_freqs) {
        // tokens will contain the key of the map in vector-of-words form
        tokens = split_line(key_val.first);
        
        // copying the first n-1 elements of the ngram to the vector wn1
        for (auto i = ngram.begin(); i != ngram.end()-1; ++i) {
            wn1.push_back(*i);
        }
        
        // popping the tokens temporarily to equality check the first n-1 elements
        tokens_head = tokens.back();
        tokens.pop_back();
        
        if (wn1 == tokens) {
            tokens.push_back(tokens_head);
            sum += get_c_star(tokens, ngram_freqs, freq_freqs);
        }
        
        // clearing stuff for the next iteration
        wn1.clear();
        tokens.clear();
    }

    return c_star / sum;
}

double get_c_star(vector<string> ngram,
                  const map<string, int> &ngram_freqs,
                  map<int, int> &freq_freqs)
{
    // first we get the ngram's count
    auto c_it = ngram_freqs.find(nmap_to_string(ngram));
    assert( c_it != ngram_freqs.end() );
    int c = c_it->second;

    // now we get Nc and Nc+1 (using interpolation if either of them happen to
    // be zero)
    double nc = freq_freqs[c];
    double nc1 = freq_freqs[c + 1];

    ensure_nonzero(&nc, freq_freqs);
    ensure_nonzero(&nc1, freq_freqs);

    // using the Good-Turing formula to calculate a new count
    double c_star = (c + 1) * (nc1 / nc);
    return c_star;
}

/*
 * if the given parameter c is 0, give it an interpolated value
 */
void ensure_nonzero(double *c, const map<int, int> &ncs)
{
    if (*c == 0) {
        // *c = interpolated_value(*c, ncs);
        //cout << "Warning: count of zero" << endl;
        *c = 1;
    }
}

/*
 * calculates the probability of a sentence occurring
 */
double smoothed_sentence_probability(const vector<string> &words, int n,
                                     map<string, int> &nfreqs,
                                     const map<string, int> &unaries)
{
    vector<string> substring;
    double probability = 1;
    int m = words.size();

    map<int, int> freq_freqs = nc_construct(nfreqs, unaries.size());

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
        probability *= smoothed_probability(substring, nfreqs, freq_freqs);
        substring.clear();
    }

    return probability;
}

void print_all_sentence_probs(char *file_path, int n, 
                              map<string, int> &nfreqs,
                              map<string, int> &unaries)
{
    ifstream file(file_path);
    
    double prob;
    string line;
    vector<string> words;
    while (file.good()) {
        getline(file, line);
        words = split_line(line);
        
        prob = smoothed_sentence_probability(words, n, nfreqs, unaries);
        cout << "\nSentence: " << line << endl;
        cout << "Probability: " << prob << endl;
    }
}
