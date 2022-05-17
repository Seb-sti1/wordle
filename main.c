#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 
#include <errno.h>
#include <math.h>

#include "word.h"
#include "bot.h"
#include "utils.h"
#include "entropy.h"

int wordSize;
int dictionaryUsed;
char* toFind;

/**
 * @brief ask for a string of 5 char. This function will not return until a string of 5 char is given by the user.
 * 
 * @param wordSize 
 * @return char* a string of 5 char
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

/**
 * @brief ask for a usigned integer. This function will not return until an unsigned integer is given by the user.
 * 
 * @return int the int
 */
int askUInt() {
    
    int i = -1;
    int match = fscanf(stdin, "%d", &i);

    if (!match || i < 0) {
        if (!match) {
            // go to the end of the stream
            char t[1];
            fscanf(stdin, "%s", t);
        }

        printf("Ceci n'est pas un entier positif !\n");
        return askUInt();
    } else {
        return i;
    }
}


int askChoice(char* choices[], int nbrOfChoices) {
    for (int i = 0; i < nbrOfChoices; i++) {
        printf("%d) %s\n", i, choices[i]);
    }

    int ans = askUInt();

    while(ans > nbrOfChoices) {
        printf("Ce choix n'existe pas !");
        ans = askUInt();
    } 

    return ans;
}


void playRoutine() {
    printf("Par defaut, ce jeu se joue avec des mots de 5 lettres. Avec combien de lettre souhaitez vous jouer ?\n");
    wordSize = askUInt(); // BUG if the user input 0


    char* dictionaryPath[3] = {
        "./french_all_size.txt",
        "./english_all_size.txt",
        "./creole_haitien_all_size.txt"//https://www.potomitan.info/vedrine/lexique_index.php#a
    };

    char* dictionaryName[3] = {
        "Français toutes tailles de mots",
        "Anglais toutes tailles de mots",
        "Créole Haitien toutes tailles de mots"
    };

    printf("Choisissez le dictionnaire à utiliser :\n");
    dictionaryUsed = askChoice(dictionaryName, 3);


    if (!loadDict(dictionaryPath[dictionaryUsed], wordSize)) {
        printf("La liste n'a pas pu être chargée !\n");
        exit(-1);
    }

    printf("Il y a %d mots dans le dictionnaire !\n", getDictionarySize());

    if (getDictionarySize() <= 0) {
        printf("Il n'y a pas de mot dans le dictionnaire chargé !\n");
    } 

    toFind = randomWord();
}


void humanPlay() {
    printf("A vous de jouer !\n");
        
    int tries = 0;
    bool won = false;

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
        printf("\033[1;32mBravo !!!\033[0;37m Vous avez trouvé le mot en %d tentative(s).\n", tries);
    } else {
        printf("Dommage :'(... Le mot était %s. Tu auras plus de chance la prochaine fois hihi ^^ !\n", toFind);
    }

    destroyDictonary();    
}

void botPlay() {
    int tries = 0;
    bool won = false;

    char** dictionary = getDictionary();
    int dictSize = getDictionarySize();

    printf("Choisissez un bot pour cette partie :\n");

    char* choices[4] = {"bot entropy corrigé",
                        "bot entropy cassé",
                        "bot occurence (somme de la fréquence de chaque lettre)",
                        "bot occurence (produit de la fréquence de chaque lettre)"};

    int botType = askChoice(choices, 4);

    printf("C'est parti !\n");

    while (tries < 6 && !won) {
        char* botWord;

        // choose the word to play
        switch (botType) {
        case 0: // entropy fixed
            if (tries == 0 && wordSize == 5 && dictionaryUsed == 0) {
                botWord = "tarie";
            } else {
                botWord = getBestWordWithEntropy(wordSize, dictionary, dictSize);
            }
            break;
        case 1: // entropy broken
            if (tries == 0 && wordSize == 5 && dictionaryUsed == 0) {
                    botWord = "aeree";
            } else {
                botWord = getBestWordWithEntropy_broken(wordSize, dictionary, dictSize);
            }
            break;
        case 2: // sum freq letters
            botWord = getBestWordWithOccurence(wordSize, dictionary, dictSize, true);
            break;
        case 3: // product freq letters
            botWord = getBestWordWithOccurence(wordSize, dictionary, dictSize, false);
            break;
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

            char** tempdictionary = compatibleWords(botWord, wordSize, verif, dictionary, dictSize, &dictSize);
            dictionary = tempdictionary; // TODO prevent memory leak without deleting the main dictonary

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
        printf("Que souhaitez-vous faire ?\n");

        printf("0) Afficher les règles de wordle\n");
        printf("1) Jouer à wordle\n");
        printf("2) Faire jouer un bot\n");

        printf("8) Pour des testes\n");
        printf("9) Quitter\n");

        int i = -1;
        int match = fscanf(stdin, "%d", &i);

        switch (i)
        {
        case 0:
            // TODO print rules
            break;
        case 1:
            playRoutine();
            humanPlay();
            break;
        case 2:
            playRoutine();
            botPlay();
            break;
        case 8:
            playRoutine();

            //char** dict = getDictionary();
            //int dictSize = getDictionarySize();

            
           
            /*
            // permet de trouver quel mot est boosté par l'algo entropy cassé
            // tetee avec +11,75 par rapport à l'entropy fonctionnelle
            char* wordtofind;
            float diff = -100;


            for (int wordIdx = 0; wordIdx < getDictionarySize(); wordIdx++) { // for every word in the dictionnary

                char* word = getDictionary()[wordIdx];

                float entropy = computeEntropy(word, 5, getDictionary(), getDictionarySize());
                float entropybro = computeEntropy_broken(word, 5, getDictionary(), getDictionarySize());
                
                if (fabs(entropybro - entropy) > diff) {
                    wordtofind = word;
                    diff = fabs(entropybro - entropy);
                }
                printf("%s :\t\t%.2f %.2f | %.2f\n", word, entropy, entropybro, fabs(entropybro - entropy));
            }

            printf("%s %f \n", wordtofind, diff);*/


 /*

            // permet de trouver un pattern où le nombre de mot compatible est tres different entre entropy corrigé et entropy cassé
            // pattern 122 (1778 en plus) ou 124 (1778 en plus) ou 148 (1597 en plus)


            char* word = "tetee";

            int patternExample;
            int delta = -1;

            for (int i = 0; i < pow(3, wordSize); i ++ ) { // for every pattern that could possibly happen

                int* pattern = toBase3(i, wordSize);
                int nbr = -1;
                int nbrBro = -1;

                
                // get how many words are compatible with the given pattern
                char** garbage = compatibleWords(word, wordSize, pattern, dict, dictSize, &nbr);
                free(garbage);
                
                garbage = compatibleWords_broken(word, wordSize, pattern, dict, dictSize, &nbrBro);
                free(garbage);

                if (abs(nbrBro - nbr) > delta) {
                    delta = abs(nbrBro - nbr);
                    patternExample = i;
                }

                printf("%d) %d %d %d\n ", i, nbr, nbrBro, abs(nbrBro - nbr));
                
                free(pattern);
            }

            printf("\n\n%d\n", patternExample);

            for (int i = 0; i < wordSize; i++) {
                printCharInColor(toBase3(patternExample, wordSize)[i], word[i]);
            }
            */

            /*
            char* word = "tetee";

            int* pattern = toBase3(122, wordSize);

            for (int i = 0; i < wordSize; i++) {
                printCharInColor(pattern[i], word[i]);
            }
            printf("\n");
            int nbr = -1;

            // get how many words are compatible with the given pattern
            char** comp = compatibleWords_broken(word, wordSize, pattern, dict, dictSize, &nbr);
            
            for (int i = 0; i < nbr; i++) {

                if (comp[i][1] != 'e' && comp[i][3] != 'e' && comp[i][4] != 'e') {
                    printf("%s\n", comp[i]);

                    
                    int* verif = verifyWord(comp[i], word);
            
                    for (int j = 0; j < wordSize; j++) {
                        printCharInColor(verif[j], comp[i][j]);
                    }

                    printf("\n");
                    
                    free(verif);
                }
            }

            free(pattern);*/

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