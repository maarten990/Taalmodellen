#include "smoothing.h"

// ugly ass global variables to hold the interpolation parameters because
// fuck me if I'm going to change every existing function to take another two parameters
double g_a = 0;
double g_b = 0;

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

    int max_value = nmap[keys[0]];


    // Nc with c = 0 will be interpolated like the rest
    Ncs[0] = 0;

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
    for (int i = 1 ; i < Ncs.size(); i++){
        if(Ncs[i] != 0){
            pointy = Ncs[i];
            pointx = i;
            break;
        }
    }
    
    // from the back, look for the first frequency with a >1 frequency
    int pointx2;
    int pointy2;
    for (int i = Ncs.size() - 1; i > 0; --i) {
        if (Ncs[i] > 10) {
            pointx2 = i;
            pointy2 = Ncs[i];
            break;
        }
    }
    
    Point point_left(pointx, pointy);
    Point point_right(pointx2, pointy2);
    
    //calculate a and b
    // WARNING: these are the a and b as specified in Jurasky & Martin; b is the slope while a is the intercept
    g_a = ( log(point_left.x) * log(point_right.y) - log(point_right.x) * log(point_left.y) )
               / // division line
               ( log(point_left.x) - log(point_right.x) );
    
    g_b = ( log(point_left.y) - log(point_right.y) )
               /
               ( log(point_left.x) - log(point_right.x) );
}

double interpolate ( int x )
{
    return exp(g_a + g_b + log(x));
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
    
    // if no words have matched, just return 0 and get it over with
    if (sum == 0)
        return 0;

    return c_star / sum;
}

double get_c_star(vector<string> ngram,
                  const map<string, int> &ngram_freqs,
                  map<int, int> &freq_freqs)
{
    // first we get the ngram's count
    auto c_it = ngram_freqs.find(nmap_to_string(ngram));
    int c;
    if (c_it != ngram_freqs.end())
        c = c_it->second;
    else
        c = 0;

    // now we get Nc and Nc+1 (using interpolation if either of them happen to
    // be zero)
    double nc = freq_freqs[c];
    double nc1 = freq_freqs[c + 1];

    ensure_nonzero(c, &nc, freq_freqs);
    ensure_nonzero(c+1, &nc1, freq_freqs);

    // using the Good-Turing formula to calculate a new count
    double c_star = (c + 1) * (nc1 / nc);
    return c_star;
}



/*
 * returns the smoothed probability of an ngram
 *
 * parameters:
 * ngram - a vector of strings representing the ngram
 * ngram_freqs - a map of all known ngrams and their frequency
 * freq_freqs - a map of Nc, the amount of ngrams having a certain frequency
 */
double smoothed_probability_backoff(vector<string> ngram,
                            const map<string, int> &ngram_freqs,
                            map<int, int> &freq_freqs, int k)
{

    // first we got the top part of the division
    double c_star = get_c_star_backoff(ngram, ngram_freqs, freq_freqs, k);
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





// new c_star backoff with int k to know when backoff should be done
double get_c_star_backoff(vector<string> ngram,
                          const map<string, int> &ngram_freqs,
                          map<int, int> &freq_freqs, int k)
{

    // first we get the ngram's count
    auto c_it = ngram_freqs.find(nmap_to_string(ngram));
    int c;
    if (c_it != ngram_freqs.end())
        c = c_it->second;
    else
        c = 0;

    // now we get Nc and Nc+1 (using interpolation if either of them happen to
    // be zero)
    double nc = freq_freqs[c];
    double nc1 = freq_freqs[c + 1];

    ensure_nonzero(c, &nc, freq_freqs);
    ensure_nonzero(c+1, &nc1, freq_freqs);
    
    double c_star;
    // in case count = 0
    if(c == 0 ){

        // using the Good-Turing formula to calculate a new count
        c_star = (c + 1) * (nc1 / nc);
    }
    else if(c <= k)
    {
        c_star = (((c+1)*(nc1/nc))-c *(((k+1)*freq_freqs[k+1])/freq_freqs[1]))/
                1-((k+1)*freq_freqs[k+1]/freq_freqs[1]);
    }
    else{
        c_star = c;
    }
    return c_star;
}

/*
 * if the given parameter c is 0, give it an interpolated value
 */
void ensure_nonzero(int c, double *nc, const map<int, int> &ncs)
{
    if (*nc == 0) {
        *nc = interpolate(c);
    }
}

/*
 * calculates the probability of a sentence occurring
 */
double smoothed_sentence_probability(const vector<string> &words, int n,
                                     map<string, int> &nfreqs,
                                     const map<string, int> &unaries,
                                     bool katz)
{
    vector<string> substring;
    double probability_log = 0;
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
        double temp_debug;
        if (katz)
            temp_debug = smoothed_probability_backoff(substring, nfreqs, freq_freqs, 5);
        else
            temp_debug = smoothed_probability(substring, nfreqs, freq_freqs);

        // protecting against invalid values
        if (temp_debug != 0)
            probability_log += log(temp_debug);
        substring.clear();
    }

    return exp(probability_log);
}

void print_all_sentence_probs(char *file_path, int n, 
                              map<string, int> &nfreqs,
                              map<string, int> &unaries,
                              bool katz)
{
    ifstream file(file_path);

    double prob;
    string line;
    double max_value = 0;
    string max_line;
    vector<string> words;
    while (file.good()) {
        getline(file, line);
        words = split_line(line);
        
        prob = smoothed_sentence_probability(words, n, nfreqs, unaries, katz);
        if(prob > max_value && line != ""){
            max_value = prob;
            max_line = line;
        }
        //cout << "\nSentence: " << line << endl;
        //cout << "Probability: " << prob << endl;
    }
    cout << max_line << endl;
}
