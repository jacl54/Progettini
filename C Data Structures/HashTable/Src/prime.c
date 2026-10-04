#include <stdlib.h>
#include <math.h>

#include "prime.h"

int nextPrime(int x){
    while(isPrime(x)!=1){
        x++;
    }
    return x;
}

int isPrime(int x){
    if(x<2){return -1;}
    if(x<4){return 1;}
    if(x%2==0){return 0;}
    //sommo 2 perchè in ogni caso se è divisibile per un numero pari lo è anche per 2 e abbiamo constatato non sia cosi
    for(int i=3; i<=floor(sqrt((double)x)); i+=2){
        if(x%i==0){return 0;}
    }
    return 1;
}