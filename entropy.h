#ifndef ENTROPY_H_   /* Include guard */
#define ENTROPY_H_

/**
 * @brief compute entropy for a given word
 * 
 * @param word the word
 * @param wordSize the size of word
 * @param dictionary the dictionary
 * @param dictionarySize the size of the dictionnary
 * @return float the entropy
 */
float computeEntropy(char* word, int wordSize, char** dictionary, int dictionarySize);


/**
 * @deprecated
 * 
 * @brief compute entropy for a given word but it uses a broken algorithm to find the compatible words
 * 
 * @param word the word
 * @param wordSize the size of word
 * @param dictionary the dictionary
 * @param dictionarySize the size of the dictionnary
 * @return float the entropy
 */
float computeEntropy_broken(char* word, int wordSize, char** dictionary, int dictionarySize);

#endif // ENTROPY_H_