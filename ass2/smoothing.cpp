#include "smoothing.h"

// calculating the Ncs
map<int, double> nc_construct(map<string, int> &nmap, int unaries_size){
    // Nc map;
    map<int, double> Ncs;
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
void simple_gt(map<int, double> &Ncs){
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


