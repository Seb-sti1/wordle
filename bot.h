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

/**
 * @brief for every words in testWords it test if it is compatible with the patten and the word
 * 
 * @param word the word
 * @param testword the word to test the compatibility
 * @param pattern the pattern (0 = char are the same, 1 = char are different, 2 = misposed)
 * @param wordSize the size of the words
 * @param testWords the words to test (an array)
 * @param testWordsSize the size of the array
 * @param numberOfCompatibleWord the number of compatible word (the size of the return array)
 * @return the words that are compatibles
 */
char** compatibleWords(char* word, int wordSize, int* pattern, char* testWords[], int testWordsSize, int* numberOfCompatibleWord);

/**
 * @brief Get the best possible word base on the entropy of each word in the given dictionary
 * 
 * @param wordSize the size of the word (number of letters)
 * @param dictionary the dictionary
 * @param dictionarySize the size of the dictionary
 * @return char* the best word
 */
char* getBestWordWithEntropy(int wordSize, char** dictionary, int dictionarySize);


/**
 * @brief Get the Best Word With Occurence (of letter). Warning only work with a French dictionary
 * 
 * @param wordSize the size of the word (number of letters)
 * @param dictionary the dictionary
 * @param dictionarySize the size of the dictionary
 * @param sumOccurrence if the score is the sum of the score of each letters or the product
 * @return char* the best word
 */
char* getBestWordWithOccurence(int wordSize, char** dictionary, int dictionarySize, bool sumOccurrence);

/**
 * @deprecated
 * 
 * @brief test the testword is compatible with word and the certain pattern
 * 
 * @param word the word
 * @param testword the word to test the compatibility
 * @param pattern the pattern (0 = char are the same, 1 = char are different, 2 = misposed)
 * @param wordSize the size of the words
 * @return true if the two are compatible
 * @return false if the two aren't compatible
 */
bool isCompatible_broken(char* word, int wordSize, int* pattern, char* testWord);


#endif // WORLD_H_