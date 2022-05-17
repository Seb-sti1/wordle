#ifndef OCCURENCE_H_   /* Include guard */
#define OCCURENCE_H_

/**
 * @brief Occurence-based function. Each letter has a score that translate to its occurence in the french language. This one sums every individual scores and returns it.
 * 
 * @param word word which score is to be calculated
 * @param wordSize word length
 * @return int 
 */
int scoreSum(char* word, int wordSize);

/**
 * @brief Occurence-based function. Each letter has a score that translate to its occurence in the french language. This one multiplies every individual scores and returns it.
 * 
 * @param word word which score is to be calculated
 * @param wordSize word length
 * @return int 
 */
int scoreMux(char* word, int wordSize);

#endif // OCCURENCE_H_