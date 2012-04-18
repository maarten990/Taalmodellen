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

    //calculate a
    double a =  ((double)(Ncs.size()-1 - pointy)/(double)(Ncs[Ncs.size()-1] - pointx));
    cout << a << endl;
    // calculate b
    double b = (double) pointy - a * pointx;
    cout << b << endl;

    // calculate new values for Ncs
    for ( auto &i:Ncs){
        if(i.second == 0 ){
            Ncs[i.first] = exp(log(i.first) * a + b);
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
    double new_c = (c + 1) * (nc1 / nc);

    // getting the value of N
    int N;
    for (auto &pair : freq_freqs) {
        N += pair.first * pair.second;
    }

    return new_c / ngram_freqs.size();
}

/*
 * if the given parameter c is 0, give it an interpolated value
 */
void ensure_nonzero(double *c, const map<int, int> &ncs)
{
    if (*c == 0) {
        // *c = interpolated_value(*c, ncs);
    }
}
