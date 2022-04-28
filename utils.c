
#include <stdlib.h>


// https://fr.wikipedia.org/wiki/Table_des_bases
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