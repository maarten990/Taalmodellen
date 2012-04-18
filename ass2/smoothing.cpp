#include "smoothing.h"

// calculating the Ncs
map<int, int> nc_construct(map<string, int> &nmap, int unaries_size){
    // Nc map;
    map<int, int> Ncs;
    // Nc with c = 0 gets all the rest of the size
    Ncs[0] = (nmap.size()*nmap.size()) - unaries_size;

    for(int c = 1 ; c < max_value; c ++){
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


