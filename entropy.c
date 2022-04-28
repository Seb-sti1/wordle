#include "bot.h"
#include "utils.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct wordScore {
    char* word;
    float score;
};



struct wordScore** computeEntropy(char* word, int wordSize, char** dictionary, int dictionarySize) {

    struct wordScore** wordScores = malloc(sizeof(struct wordScore) * dictionarySize);

    for (int wordIdx = 0; wordIdx < dictionarySize; wordIdx++) { // for every word in the dictionnary

        char* word = dictionary[wordIdx];


        struct wordScore* score = malloc(sizeof(struct wordScore) * dictionarySize);

        score->word = word;
        score->score = 0;

        for (int i = 0; i < pow(3, wordSize); i ++ ) { // for every pattern that could possibly happen

            int* pattern = toBase3(i, wordSize);
            int numberOfCompatibleWord = -1;

            
            // get how many words are compatible with the given pattern
            compatibleWords(word, wordSize, pattern, dictionary, dictionarySize, &numberOfCompatibleWord);

            float p = numberOfCompatibleWord/dictionarySize; // the portion of the dictionnary

            score->score += -p*log2(p);
            // add p * log_2(1/p) at the score (it's the entropy)

            free(pattern);
        }
    }

    return wordScores;
}
 
