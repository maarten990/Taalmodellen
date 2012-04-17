#include "smoothing.h"

/* Good-Turing smoothing is used to calculate probability
  of thins we haven't seen in the dataset*/
void gt_smoothing(map<string, int> nmap, int n,int size_unaries)
{
    // for all the values in nmap we will calculate GT smoothing
    int max_value = nmap[0];
    int size = nmap.size();
    int Nc1 = 0;
    int c_star = 0;

    // deal with possible zero values
    map<int, int> Ncs = simple_gt(nmap, size_unaries);
   V
    // the c = 0 case. CAUTION: ONY WORKS FOR BIGRAMS
    int Nc =(size unaries * size_unaries) - nmap.size()

    // we loop until maxvalue (first value in sorted map)
    for(int c = 1 ; c < max_value; c ++){

        // incrementing Nc1 value
        while( nmaps[size] == c){
            Nc1 ++;
            size --;
        }
        if(Nc1 == 0) {
        // we have a serious problem !!!
        }
        else{
            //calculations
            c_star = (c - 1) * (Nc1/Nc)
        }
        // Nc1 becomes our new Nc
        Nc = Nc1;

    }
}

// calculating the Ncs with simple good turing
map<int, int> simple_gt(map<string, int> &nmap, int unaries_size){
    // Nc map;
    map<int, int> Ncs;
    int max_value = nmap[0];
    int size = nmap.size()-1;
    // Nc with c = 0 gets all the rest of the size
    Ncs[0] = (nmap.size()*nmap.size()) - unaries_size;

    for(int c = 1 ; c < max_value; c ++){
        Ncs[c] = 0;
        // incrementing Nc value
        for( pair <string, int> &i: nmap){
            if(i.second == c){
                Ncs[c] +=1;
        }
    }
    //now that we have filled the Ncs map we only need to change the 0 values
        f(n) a+b*log(n)
    int counter = 0 ;
    int pointx = 0;
    int pointy = 0;
    int pointx2 = 0;
    int pointy2 = 0;
    for( pair<int, int> &i: Ncs){
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

    if(counter <2){
    cout << "Not enough data" << endl;
    }
    //calculate a
    int a = (pointy2 - pointy)/(pointx2 - pointx);
    // calculate b
    int b = pointy - a * pointx;
    for ( pair<int, int> &i:Ncs){
        if( i.last == 0){
        Ncs[i.first] = log( log(i.first)*a + b);
        }
    }
    return Ncs;

}

