#ifndef UTILS_H_   /* Include guard */
#define UTILS_H_


/**
 * @brief parse a integer to a base 3 array
 * 
 * @param n the integer 
 * @param arraySize the max size of the array
 * @return int* the array
 */
int* toBase3(int n, int arraySize);


/**
 * @brief converte an array in base 3 to an integer
 * 
 * @param array the array 
 * @param arraySize the size array
 * @return int the integer
 */
int fromBase3(int* array, int arraySize);


#endif // UTILS_H_