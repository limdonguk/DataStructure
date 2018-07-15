#include <stdio.h>
#include <stdlib.h>

int factorial(int n){
    int ret = 0;
    if(n <= 1) {
        ret = 1;
    }
    else {
        ret = n * factorial(n-1);
    }
    return ret;
}

