#include <string.h>


percentage[26];
percentage = {764,90,326,367,1472,107,87,74,753,61,7,546,297,710,580,252,136,669,795,631,134,5,4,113}; //letter occurence in 1:10 000 to keep integer.

int scoreSum(char* word, int wordSize) {        //first score, adding every occurence value.
    int score = 0;
    for (int i = 0; i < wordSize; i++) {
        int index = (word[i]) -97;
        score += percentage[index];
    }
    return score;
}

int scoreMux(char* word, int wordSize) {        //second score, multiplying everyu occurence value._u
    int score = 0;
    for (int i = 0; i < wordSize; i++) {
        int index = (word[i]) -97;
        score *= percentage[index];
    }
    return score;
}


char* getBestWordWithOccurence(int wordSize, char** dictionary, int dictionarySize) {

    char* bestWord = "";
    float bestScore = 0;


    for (int wordIdx = 0; wordIdx < dictionarySize; wordIdx++) { // for every word in the dictionnary

        char* word = dictionary[wordIdx];

        int score = scoreSum(word, wordSize);
                                                                //choose best algorithm.
        //int score = scoreMux(word, wordSize);

        if (bestScore < score) {
            bestWord = word;
            bestScore = score;
        }
    }

    return bestWord;
}