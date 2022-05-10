#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 
#include <errno.h>

#include "word.h"
#include "bot.h"
#include "entropy.h"


/**
 * @brief print c with a specific color
 * 
 * @param validation : the stat of the caracter (given by verifyWord)
 * @param c : the char
 */
void printCharInColor(int validation, char c) {
    switch (validation) {
    case 0:
        printf("\033[1;32m%c\033[0;37m", c);
        break;
    case 1:
        printf("\033[1;31m%c\033[0;37m", c);
        break;    
    case 2:
        printf("\033[1;33m%c\033[0;37m", c);
        break;   
    default:
        break;
    }

}




/**
 * ask for a string of 5 char
 * 
 * return : char* a string of 5 char or NULL (on error)
 * 
 */
char* askWord(int wordSize) {

    char* userWord = malloc(sizeof(char*)*(wordSize+1));
    userWord[wordSize] = '\0';


    char mot [42];                      //because réponse à la vie
    fscanf(stdin, "%s", mot);
    
    int len = strlen(mot);

    if (len != wordSize) {
        printf("Attention ! Le mot ne fait pas %d lettres.\n", wordSize);
        return askWord(wordSize);
    }

    if (!searchDict(mot)) {
        printf("Le mot n'est pas dans le dictionnaire.\n");
        return askWord(wordSize);
    }

    strcpy(userWord, mot);

    return userWord;
}

void humanPlay() {
    int tries = 0;
    bool won = false;

    // TODO : add word size
    int wordSize = 5;

    // TODO : Choix du dictionnaire
    printf("Chargemenent de la liste de mots...\n");
    
    if (loadDict("./liste_complete_triee.txt", wordSize)) {
        printf("La liste a été correctement chargée !\n");
    } else {
        printf("La liste n'a pas pu être chargée !\n");
        exit(-1);
    }


    printf("Choix d'un mot aléatoire !\n");
    char* toFind = randomWord();


    while (tries < 6 && !won) {
        char* userWord = askWord(wordSize);

        //check if the word exist
        if (searchDict(userWord)) {
            
            if (strcmp(toFind, userWord) == 0) {
                won = true;
            } else {
                // compare with the words
                int* verif = verifyWord(toFind, userWord);
                
                for (int i = 0; i < wordSize; i++) {
                    printCharInColor(verif[i], userWord[i]);
                }
                printf("\n");

                free(verif);
            }

            tries++;
        } else {
            printf("Ce mot n'existe pas !\n");
        }

        free(userWord);
    }

    if (won) {
        printf("Bravo !!! Vous avez trouvé le mot en %d tentative(s).\n", tries);
    } else {
        printf("Dommage :'(... Le mot était %s. Tu auras plus de chance la prochaine fois hihi ^^ !\n", toFind);
    }

    
    destroyDictonary();
        
}

void botPlayWithEntropy() {
    int tries = 0;
    bool won = false;

    // TODO : add word size
    int wordSize = 5;

    // TODO : Choix du dictionnaire
    printf("Chargemenent de la liste de mots...\n");
    
    if (loadDict("./liste_complete_triee.txt", wordSize)) {
        printf("La liste a été correctement chargée !\n");
    } else {
        printf("La liste n'a pas pu être chargée !\n");
        exit(-1);
    }


    printf("Choix d'un mot aléatoire !\n");
    char* toFind = randomWord();

    char** dictionary = getDictionary();
    int dictSize = getDictionarySize();


    while (tries < 6 && !won) {
        char* botWord;


        if (tries == 0 && wordSize == 5) {
            botWord = "aeree";
        } else {
            botWord = getBestWordWithEntropy(wordSize, dictionary, dictSize);
        }
        
        printf("Le bot joue %s\n", botWord);

        if (strcmp(toFind, botWord) == 0) {
            won = true;
        } else {
            // compare with the words
            int* verif = verifyWord(toFind, botWord);
            
            for (int i = 0; i < wordSize; i++) {
                printCharInColor(verif[i], botWord[i]);
            }
            printf("\n");


            printf("%s\n", dictionary[0]);

            char** tempdictionary = compatibleWords(botWord, wordSize, verif, dictionary, dictSize, &dictSize);
            dictionary = tempdictionary;

            free(verif);
        }

        tries++;
    }

    if (won) {
        printf("Le bot a trouvé en %d tentative(s).\n", tries);
    } else {
        printf("Le bot n'a pas trouvé le mot %s...\n", toFind);
    }

    
    destroyDictonary();
}


int main(int argc, char const *argv[])
{
    printf("Bienvenue dans le wordle d'IN104 !\n");
    printf("Par Sébastien Kerbourc'h et Adrien Wallon\n\n");

    bool running = true;
    while (running) {
        printf("Que souhaitez vous faire ?\n");
        printf("1) Jouer à wordle\n");
        printf("2) Faire jouer le bot (entropy)\n");


        printf("8) Pour des testes\n");

        printf("9) Quitter\n");

        int i = -1;
        int match = fscanf(stdin, "%d", &i);

        switch (i)
        {
        case 1:
            humanPlay();
            break;
        case 2:
            botPlayWithEntropy();
            break;
        case 8:
            // TODO : Choix du dictionnaire
            printf("Chargemenent de la liste de mots...\n");
            
            if (loadDict("./liste_complete_triee.txt", 5)) {
                printf("La liste a été correctement chargée !\n");
            } else {
                printf("La liste n'a pas pu être chargée !\n");
                exit(-1);
            }

            /*
            int num = 0;
            
            int pattern[5] = {0,1,2,0,1};

            char** compatible = compatibleWords("abaca", 5, pattern, getDictionary(), getDictionarySize(), &num);

            for (int j = 0; j < num; j++) {
                printf("%s\n", compatible[j]);
            } 
            */


            for (int wordIdx = 0; wordIdx < getDictionarySize(); wordIdx++) { // for every word in the dictionnary

                char* word = getDictionary()[wordIdx];

                float entropy = computeEntropy(word, 5, getDictionary(), getDictionarySize());

                printf("%s : %f", word, entropy);
            }
            break;
        case 9:
            printf("A+ :-)");
            running = false;
            break;
        default:
            printf("Cette option n'existe pas...\n");

            if (!match) {
                // go to the end of the stream
                char t[1];
                fscanf(stdin, "%s", t);
            }
            break;
        }

    }
    
    return 0;
}


void displayIntArray(int* array, int size) { // to remove

    for (int i = 0; i < size; i++) {
        printf("|%d", array[i]); 
    }
    printf("|\n");

}