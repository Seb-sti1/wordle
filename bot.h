#ifndef BOT_H_   /* Include guard */
#define BOT_H_

#include <stdbool.h>

/**
 * @brief test the testword is compatible with word and the certain pattern
 * 
 * @param word the word
 * @param testword the word to test the compatibility
 * @param pattern the pattern (0 = char are the same, 1 = char are different, 2 = misposed)
 * @param wordSize the size of the words
 * @return true if the two are compatible
 * @return false if the two aren't compatible
 */
bool isCompatible(char* word, int wordSize, int* pattern, char* testWord);


/** //todo
 * @brief 
 * 
 */
char** compatibleWords(char* word, int wordSize, int* pattern, char* testWords[], int testWordsSize, int* numberOfCompatibleWord);




#endif // WORLD_H_