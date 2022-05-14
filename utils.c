
#include <stdlib.h>
#include <stdio.h>


int* toBase3(int n, int arraySize) {

    int* array = malloc(sizeof(int)*arraySize);

    for (int i = arraySize - 1; i >=0; i--) {

        array[i] = n % 3;
        
        n = n / 3;

    } 

    return array;
}


int fromBase3(int* array, int arraySize) {

    int n = 0;

    int power = 1;

    for (int i = 0; i < arraySize; i++) {

        n += array[i]*power;

        power *= 3;
    } 

    return power;

}

void printCharInColor(int validation, char c) {
    switch (validation) {
    case 0:
        printf("\033[1;32m%c\033[0;37m", c);
        break;
    case 1:
        printf("\033[1;31m%c\033[0;37m", c);
        break;    
    case 2:
        printf("\033[1;33m%c\033[0;37m", c);
        break;   
    default:
        break;
    }

}
