#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "bot.h"
#include "utils.h"
#include "word.h"


float computeEntropy(char* word, int wordSize, char** dictionary, int dictionarySize) {

    float entropy = 0;

    for (int i = 0; i < pow(3, wordSize); i ++ ) { // for every pattern that could possibly happen

        int* pattern = toBase3(i, wordSize);
        int numberOfCompatibleWord = -1;

        
        // get how many words are compatible with the given pattern
        char** garbage = compatibleWords(word, wordSize, pattern, dictionary, dictionarySize, &numberOfCompatibleWord);
        free(garbage);

        if (numberOfCompatibleWord > 0) {
            //float p = numberOfCompatibleWord/dictionarySize; // the portion of the dictionnary
            
            // add p * log_2(1/p) at the score (it's the entropy)
            entropy += ((float) numberOfCompatibleWord)/dictionarySize*log2(((float) dictionarySize)/numberOfCompatibleWord);
        }

        free(pattern);
    }

    return entropy;
}

float computeEntropyOptimized(char* word, int wordSize, char** dictionary, int dictionarySize) {
    int numberOfPattern = pow(3, wordSize);

    int numberOfCompatibleWordPerPattern[numberOfPattern];
    for (int i = 0; i < numberOfPattern; i++) {
        numberOfCompatibleWordPerPattern[i] = 0;
    }

    for (int idx = 0; idx < dictionarySize; idx++) {
        int* shouldHavePattern = verifyWord(dictionary[idx], word);

        int patternIdx = fromBase3(shouldHavePattern, wordSize);

        numberOfCompatibleWordPerPattern[patternIdx] = numberOfCompatibleWordPerPattern[patternIdx] + 1;

        free(shouldHavePattern);
    }
    
    float entropy = 0;

    for (int i = 0; i < numberOfPattern; i++) {
        int numberOfCompatibleWord = numberOfCompatibleWordPerPattern[i];

        if (numberOfCompatibleWord > 0 ) {
            entropy += ((float) numberOfCompatibleWord)/dictionarySize*log2(((float) dictionarySize)/numberOfCompatibleWord);
        }

    }

    return entropy;
}
 


float computeEntropy_broken(char* word, int wordSize, char** dictionary, int dictionarySize) {

    float entropy = 0;

    for (int i = 0; i < pow(3, wordSize); i ++ ) { // for every pattern that could possibly happen

        int* pattern = toBase3(i, wordSize);
        int numberOfCompatibleWord = -1;

        
        // get how many words are compatible with the given pattern
        char** garbage = compatibleWords_broken(word, wordSize, pattern, dictionary, dictionarySize, &numberOfCompatibleWord);
        free(garbage);

        if (numberOfCompatibleWord > 0) {
            //float p = numberOfCompatibleWord/dictionarySize; // the portion of the dictionnary
            
            // add p * log_2(1/p) at the score (it's the entropy)
            entropy += ((float) numberOfCompatibleWord)/dictionarySize*log2(((float) dictionarySize)/numberOfCompatibleWord);
        }

        free(pattern);
    }

    return entropy;
}
 