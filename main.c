#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 

#include "word.h"
#include "bot.h"


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




int main(int argc, char const *argv[])
{
    int tries = 0;
    bool won = false;

    printf("Bienvenue dans le wordle d'IN104 !\n");
    printf("Par Sébastien Kerbourc'h et Adrien Wallon\n\n");

    // TODO : add word size
    int wordSize = 5;

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


                /* too remove
                int numberOfCompatibleWord = -1;
                char** t = compatibleWords(userWord, 5, verif, getDictionary(), getDictionarySize(), &numberOfCompatibleWord);

                printf("%s\n", t[0]);

                printf("%d\n", numberOfCompatibleWord);*/

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
    
    return 0;
}


void displayIntArray(int* array, int size) { // to remove

    for (int i = 0; i < size; i++) {
        printf("|%d", array[i]); 
    }
    printf("|\n");

}