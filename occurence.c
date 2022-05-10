#include <string.h>


percentage[26];
percentage = {764,90,326,367,1472,107,87,74,753,61,7,546,297,710,580,252,136,669,795,631,134,5,4,113}; //pourcentage d'occurence en pour 10 000.

int scoreSum(char* word, int wordSize) {
    int score = 0;
    for (int i = 0; i < wordSize; i++) {
        int index = int(word[i]) -97;
        score += percentage[index];
    }
    return score;
}

int scoreMux(char* word, int wordSize) {
    int score = 0;
    for (int i = 0; i < wordSize; i++) {
        int index = int(word[i]) -97;
        score *= percentage[index];
    }
    return score;
}