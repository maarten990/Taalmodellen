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
    Ncs[0] = (nmap.size()*nmap.size()) - unaries_size;

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


map<int, int> simple_gt(map<int, int> &Ncs){
    //now that we have filled the Ncs map we only need to change the 0 values
    int counter = 0 ;
    int pointx = 0;
    int pointy = 0;
    int pointx2 = 0;
    int pointy2 = 0;
    // find two pairs where Nc != 0
    for( auto &i: Ncs){
        if(i.second != 0 && counter == 0  ){
            counter++;
            pointx = i.first;
            pointy = i.second;
           }
        if(i.second != 0 && counter == 1  ){
            counter++;
            pointx2 = i.first;
            pointy2 = i.second;
           }
        if(counter == 2){
            break;
        }
    }

    if(counter <2){
        cout << "Not enough data" << endl;
    }

    //calculate a
    int a = (pointy2 - pointy)/(pointx2 - pointx);
    // calculate b
    int b = pointy - a * pointx;
    // calculate new values for Nc = 0
    for ( auto &i:Ncs){
        if( i.second == 0){
        Ncs[i.first] = log(i.first)*a + b;
        }
    }

    return Ncs;
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
                            const map<int, int> &freq_freqs)
{
    // first we get the ngram's count
    auto c_it = ngram_freqs.find(nmap_to_string(ngram));
    assert( c != ngram_freqs.end() );
    int c = *c;

    // now we get Nc and Nc+1 (using interpolation if either of them happen to
    // be zero)
    double nc = freq_freqs(c);
    double nc1 = freq_freqs(c + 1);

    ensure_nonzero(&nc, freq_freqs);
    ensure_nonzero(&nc1, freq_freqs);

    // using the Good-Turing formula to calculate a new count
    double new_c = (c + 1) * (nc1 / nc);

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
