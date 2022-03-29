#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 
#include "mots.h"


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
    
    int i = 0;

    while (i < wordSize) {
        char c = fgetc(stdin);
        
        if (isalpha(c)) {
            userWord[i] = c;
            i++;
        }
    }


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
            }

            tries++;
        } else {
            printf("Ce mot n'existe pas !\n");
        }
    }

    if (won) {
        printf("Bravo !!! Vous avez trouvé le mot en %d tentative.\n", tries);
    } else {
        printf("Dommage :'(... Le mot était %s. Tu auras plus de chance la prochaine fois hihi ^^ !\n", toFind);
    }
    
    return 0;
}


