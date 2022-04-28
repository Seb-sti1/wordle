
#include <stdlib.h>
#include <string.h>

#include "bot.h"
#include "word.h"


bool isCompatible(char* word, int wordSize, int* pattern, char* testWord) {
    
    int requiredNumberOfApparition[26];
    bool isNumberStrict[26];

    int numberOfApparitionInTest[26];

    for (int i = 0; i < 26; i++) {
        requiredNumberOfApparition[i] = 0;
        numberOfApparitionInTest[i] = 0;
        isNumberStrict[i] = false;
    }


    for (int i = 0; i < wordSize; i++) {
        if (pattern[i] == 2 || pattern[i] == 0) {
            requiredNumberOfApparition[(int) word[i] - 97] += 1;
        }

        numberOfApparitionInTest[(int) testWord[i] - 97] += 1;

        if (pattern[i] == 1) {
            isNumberStrict[(int) word[i] - 97] = true;
        }
    }

    for (int i = 0; i < wordSize; i++) {

        if (pattern[i] == 0) { // if two char that must be identical
            if (word[i] != testWord[i]) { // but aren't
                return false; // the testword doesn't match
            }
        } else {

            if (isNumberStrict[(int) word[i] - 97]) { // if the number of word[i] must be matched stricly
                if (requiredNumberOfApparition[(int) word[i] - 97] != numberOfApparitionInTest[(int) word[i] - 97]) {
                    return false;// but there not the strict number
                }
            } else { // if the number of word[i] must be at least requiredNumberOfApparition[(int) word[i]]
                if (requiredNumberOfApparition[(int) word[i] - 97] > numberOfApparitionInTest[(int) word[i] - 97]) {
                    return false;// but there less word[i] in the testword
                }
            }
        }

    }


    return true;
}


char** compatibleWords(char* word, int wordSize, int* pattern, char* testWords[], int testWordsSize, int* numberOfCompatibleWord) {

    char** compatible = malloc(sizeof(char*)*testWordsSize);
   
    *numberOfCompatibleWord = 0;

    for (int i = 0; i < testWordsSize; i++) {
        if (isCompatible(word, wordSize, pattern, testWords[i])) {
            compatible[*numberOfCompatibleWord] = testWords[i];

            *numberOfCompatibleWord += 1;
        }
    }

    return compatible;
}