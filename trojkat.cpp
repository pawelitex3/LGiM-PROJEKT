#include "trojkat.h"

Trojkat::Trojkat(){
    for(int i=0; i<3; i++){
        wierzcholki[i] = 0;
    }
}

Trojkat::Trojkat(int w1, int w2, int w3){
    wierzcholki[0] = w1;
    wierzcholki[1] = w2;
    wierzcholki[2] = w3;
}
