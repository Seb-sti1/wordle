#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#include "word.h"
#include "bot.h"
#include "utils.h"
#include "entropy.h"

int wordSize;
int dictionaryUsed;
char *toFind;
int maxTries;

/**
 * @brief ask for a string of 5 char. This function will not return until a string of 5 char is given by the user.
 *
 * @param wordSize
 * @return char* a string of 5 char
 */
char *askWord(int wordSize)
{

    char *userWord = malloc(sizeof(char *) * (wordSize + 1));
    userWord[wordSize] = '\0';

    char mot[42]; // because réponse à la vie
    fscanf(stdin, "%s", mot);

    int len = strlen(mot);

    if (len != wordSize)
    {
        printf("Attention ! Le mot ne fait pas %d lettres.\n", wordSize);
        return askWord(wordSize);
    }

    if (!searchDict(mot))
    {
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
int askUInt()
{

    int i = -1;
    int match = fscanf(stdin, "%d", &i);

    if (!match || i < 0)
    {
        if (!match)
        {
            // go to the end of the stream
            char t[1];
            fscanf(stdin, "%s", t);
        }

        printf("Ceci n'est pas un entier positif !\n");
        return askUInt();
    }
    else
    {
        return i;
    }
}

/**
 * @brief ask to choose between multiple possibilities
 *
 * @param choices the different options
 * @param nbrOfChoices the number of options
 * @return int the option chosen
 */
int askChoice(char *choices[], int nbrOfChoices)
{
    for (int i = 0; i < nbrOfChoices; i++)
    {
        printf("%d) %s\n", i, choices[i]);
    }

    int ans = askUInt();

    while (ans > nbrOfChoices)
    {
        printf("Ce choix n'existe pas !");
        ans = askUInt();
    }

    return ans;
}

/**
 * @brief Ask for the number of letters, number of tries, the dictionary et word to find
 */
void playRoutine()
{
    printf("Ce jeu se joue avec des mots de 5 lettres. Avec combien de lettre souhaitez-vous jouer ?\n");
    wordSize = askUInt(); // BUG if the user input 0

    printf("Une partie comporte traditionnellement 6 essais. Combien en désirez-vous ?\n");
    maxTries = askUInt();

    char *dictionaryPath[3] = {
        "./french_all_size.txt",
        "./english_all_size.txt",
        "./creole_haitien_all_size.txt"};

    char *dictionaryName[3] = {
        "Français toutes tailles de mots",
        "Anglais toutes tailles de mots",
        "Créole Haitien toutes tailles de mots"};

    printf("Choisissez le dictionnaire à utiliser :\n");
    dictionaryUsed = askChoice(dictionaryName, 3);

    if (!loadDict(dictionaryPath[dictionaryUsed], wordSize))
    {
        printf("La liste n'a pas pu être chargée !\n");
        exit(-1);
    }

    printf("Il y a %d mots dans le dictionnaire !\n", getDictionarySize());

    if (getDictionarySize() <= 0)
    {
        printf("Il n'y a pas de mot dans le dictionnaire chargé !\n");
    }

    toFind = randomWord();
}

/**
 * @brief let a human play
 */
void humanPlay()
{
    printf("A vous de jouer !\n");

    int tries = 0;
    bool won = false;

    while (tries < maxTries && !won)
    {
        char *userWord = askWord(wordSize);

        // check if the word exist
        if (searchDict(userWord))
        {

            if (strcmp(toFind, userWord) == 0)
            {
                won = true;
            }
            else
            {
                // compare with the words
                int *verif = verifyWord(toFind, userWord);

                for (int i = 0; i < wordSize; i++)
                {
                    printCharInColor(verif[i], userWord[i]);
                }
                printf("\n");

                free(verif);
            }

            tries++;
        }
        else
        {
            printf("Ce mot n'existe pas !\n");
        }

        free(userWord);
    }

    if (won)
    {
        printf("\033[1;32mBravo !!!\033[0;37m Vous avez trouvé le mot en %d tentative(s).\n", tries);
    }
    else
    {
        printf("Dommage :'(... Le mot était %s. Tu auras plus de chance la prochaine fois hihi ^^ !\n", toFind);
    }

    destroyDictonary();
}

/**
 * @brief let a bot play
 *
 * @param testing: if the it's launch for testing purposes
 * @param botType: -1 = ask ; 0-4 = the bot to play
 *
 * @return int: the number of tries. if tries == maxTries then the bot failed to find the word
 */
int botPlay(bool testing, int botType)
{
    int tries = 0;
    bool won = false;

    char **dictionary = getDictionary();
    int dictSize = getDictionarySize();

    if (!testing)
    {
        printf("Choisissez un bot pour cette partie :\n");

        char *choices[4] = {"bot entropy corrigé",
                            "bot entropy cassé",
                            "bot occurence (somme de la fréquence de chaque lettre)",
                            "bot occurence (produit de la fréquence de chaque lettre)"};

        botType = askChoice(choices, 4);

        printf("C'est parti !\n");
    }

    char *firstWordFiveLetters[4][3] = {// [botIdx][dictionaryIdx]
                                        {"tarie", "tares", "kolet"},
                                        {"aeree", "seres", "kakon"},
                                        {"aeree", "essee", "prene"},
                                        {"abaca", "aahed", "abiye"}};

    char *firstWordSevenLetters[4][3] = {// [botIdx][dictionaryIdx]
                                         {"cariees", "tarlies", "kalakit"},
                                         {"cariees", "tarlies", "kalakit"}, // used the same word as above (because it would take a century to find it)
                                         {"entetee", "teepees", "malenge"},
                                         {"abaissa", "aaronic", "adonayi"}};

    char *firstWordTwelveLetters[4][3] = {// [botIdx][dictionaryIdx]
                                          {"reticulaires", "centralities", ""},
                                          {"reticulaires", "centralities", ""}, // used the same word as above (because it would take a century to find it)
                                          {"representees", "tennesseeans", ""},
                                          {"abandonnames", "abalienating", ""}};

    while (tries < maxTries && !won)
    {
        char *botWord;
        bool found = false;

        // choose the word to play
        if (tries == 0)
        {
            switch (wordSize)
            {
            case 5:
                found = true;
                botWord = firstWordFiveLetters[botType][dictionaryUsed];
                break;
            case 7:
                found = true;
                botWord = firstWordSevenLetters[botType][dictionaryUsed];
                break;
            case 12:
                found = true;
                botWord = firstWordTwelveLetters[botType][dictionaryUsed];
                break;
            default:
                printf("Info : La première tentative n'a pas été caculée.\n");
                break;
            }
        }

        if (!found)
        {
            switch (botType)
            {
            case 0: // entropy fixed
                if (tries == 0 && !testing)
                {
                    printf("Le calcul de la première tentative peut être long (~10min)\n");
                }

                botWord = getBestWordWithEntropy(wordSize, dictionary, dictSize);
                break;
            case 1: // entropy broken
                if (tries == 0 && !testing)
                {
                    printf("Attention ce bot est très lent. En fonction des paramètres utilisés, vous"
                           " pouvez décéder avant que le bot ne joue un seul coup... Les paramètres significatifs"
                           " sont : le nombre de lettre et la taille du dictionnaire.\n");
                }

                botWord = getBestWordWithEntropy_broken(wordSize, dictionary, dictSize);
                break;
            case 2: // sum freq letters
                botWord = getBestWordWithOccurence(wordSize, dictionary, dictSize, true);
                break;
            case 3: // product freq letters
                botWord = getBestWordWithOccurence(wordSize, dictionary, dictSize, false);
                break;
            }
        }

        if (!testing)
            printf("Le bot joue %s\n", botWord);

        if (strcmp(toFind, botWord) == 0)
        {
            won = true;
        }
        else
        {
            // compare with the words
            int *verif = verifyWord(toFind, botWord);

            if (!testing)
            {
                for (int i = 0; i < wordSize; i++)
                {
                    printCharInColor(verif[i], botWord[i]);
                }
                printf("\n");
            }

            char **tempdictionary = compatibleWords(botWord, wordSize, verif, dictionary, dictSize, &dictSize);
            dictionary = tempdictionary; // TODO prevent memory leak without deleting the main dictonary

            free(verif);

            tries++;
        }
    }

    if (!testing)
    {

        if (won)
        {
            printf("Le bot a trouvé en %d tentative(s).\n", tries + 1);
        }
        else
        {
            printf("Le bot n'a pas trouvé le mot %s...\n", toFind);
        }

        destroyDictonary();
    }

    return tries + 1;
}

/**
 * @brief launch the main routine
 *
 * @param argc 0
 * @param argv nothing
 * @return int end status
 */
int main(int argc, char const *argv[])
{

    char *dictionaryPath[3] = {
        "./french_all_size.txt",
        "./english_all_size.txt",
        "./creole_haitien_all_size.txt"};

    printf("Bienvenue dans le wordle d'IN104 !\n");
    printf("Par Sébastien Kerbourc'h et Adrien Wallon\n\n");

    bool running = true;
    while (running)
    {
        printf("\n\nQue souhaitez-vous faire ?\n");

        printf("0) Afficher les règles de wordle\n");
        printf("1) Jouer à wordle\n");
        printf("2) Faire jouer un bot\n");
        printf("3) Calculs des performances (attention c'est long)\n");
        printf("4) Choix des meilleurs premiers mots (attention c'est long)\n");

        printf("8) Pour des tests\n");
        printf("9) Quitter\n");

        int i = -1;
        int match = fscanf(stdin, "%d", &i);

        switch (i)
        {
        case 0:
            printf("Vous devez devinez un mot de 5 lettres en 6 essais.\nA chaque essai"
                   " le programme vous donne des indices :\nles lettres vertes correspondent aux "
                   "lettres bien placées,\nles lettres jaunes correspondent aux lettres "
                   "existantes dans le mot mais aux mauvaises endroits,\net en blanc les "
                   "lettres n'existant pas dans le mot.\n");
            break;
        case 1:
            playRoutine();
            humanPlay();
            break;
        case 2:
            playRoutine();
            botPlay(false, -1);
            break;
        case 3:
            // csv line : wordsize; dict; word; algo; time; score
            maxTries = 6;

            int errors = 0;

            FILE *dump = fopen("data.csv", "a");

            for (int wordSizeIdx = 1; wordSizeIdx < 3; wordSizeIdx++)
            {
                switch (wordSizeIdx)
                {
                case 0:
                    wordSize = 5;
                    break;
                case 1:
                    wordSize = 7;
                    break;
                case 2:
                    wordSize = 12;
                    break;
                }

                for (int dictIdx = 0; dictIdx < 3; dictIdx++)
                {
                    dictionaryUsed = dictIdx; // change dictionary

                    if (!loadDict(dictionaryPath[dictionaryUsed], wordSize))
                    {
                        printf("La liste n'a pas pu être chargée !\n");
                        exit(-1);
                    }

                    char **dictionary = getDictionary();
                    int dictSize = getDictionarySize();

                    for (int wordIdx = 0; wordIdx < dictSize; wordIdx++)
                    {
                        toFind = dictionary[wordIdx];

                        for (int botIdx = 0; botIdx < 4; botIdx++)
                        {
                            int score = -1;

                            clock_t begin = clock();
                            if (botIdx != 1)
                            {
                                score = botPlay(true, botIdx);
                            }
                            clock_t end = clock();
                            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

                            int er = fprintf(dump, "%d;%d;%s;%d;%f;%d\n", wordSize, dictIdx, toFind, botIdx, time_spent, score);
                            if (er < 0 || wordIdx % 1000 == 0)
                            {
                                printf("%d;%d;%s;%d;%f;%d\n", wordSize, dictIdx, toFind, botIdx, time_spent, score);

                                if (er < 0)
                                    errors++;
                            }
                        }

                        if (wordIdx % 1000 == 0)
                        {
                            printf("mot = %d\n", wordIdx);
                        }
                    }

                    fflush(dump);

                    destroyDictonary();
                }
            }

            printf("Tests de performance terminé ! %d erreur(s) ont eu liée.", errors);
            fclose(dump);

            break;
        case 4:
            maxTries = 6;

            errors = 0;

            FILE *bestword = fopen("entropy_best.csv", "w");

            for (int wordSizeIdx = 0; wordSizeIdx < 3; wordSizeIdx++)
            {
                switch (wordSizeIdx)
                {
                case 0:
                    wordSize = 5;
                    break;
                case 1:
                    wordSize = 7;
                    break;
                case 2:
                    wordSize = 12;
                    break;
                }

                for (int dictIdx = 0; dictIdx < 3; dictIdx++)
                {
                    dictionaryUsed = dictIdx; // change dictionary

                    if (!loadDict(dictionaryPath[dictionaryUsed], wordSize))
                    {
                        printf("La liste n'a pas pu être chargée !\n");
                        exit(-1);
                    }

                    char **dictionary = getDictionary();
                    int dictSize = getDictionarySize();

                    for (int botIdx = 0; botIdx < 4; botIdx++)
                    {
                        clock_t begin;
                        clock_t end;
                        char *botWord;

                        // choose the word to play
                        switch (botIdx)
                        {
                        case 0: // entropy fixed
                            begin = clock();
                            botWord = getBestWordWithEntropy(wordSize, dictionary, dictSize);
                            end = clock();
                            break;
                        case 1: // entropy broken
                            if (wordSize == 5 || dictIdx == 3)
                            {
                                begin = clock();
                                botWord = getBestWordWithEntropy_broken(wordSize, dictionary, dictSize);
                                end = clock();
                            }
                            else
                            {
                                begin = clock();
                                botWord = "non";
                                end = clock();
                            }

                            break;
                        case 2: // sum freq letters
                            begin = clock();
                            botWord = getBestWordWithOccurence(wordSize, dictionary, dictSize, true);
                            end = clock();
                            break;
                        case 3: // product freq letters
                            begin = clock();
                            botWord = getBestWordWithOccurence(wordSize, dictionary, dictSize, false);
                            end = clock();
                            break;
                        }

                        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                        if (fprintf(bestword, "%d;%d;%d;%f;%s\n", wordSize, dictIdx, botIdx, time_spent, botWord) < 0)
                        {
                            errors++;
                        }

                        printf("%d;%d;%d;%f;%s\n", wordSize, dictIdx, botIdx, time_spent, botWord);

                        fflush(bestword);
                    }

                    destroyDictonary();
                }
            }

            printf("%d erreur(s) ont eu lieu.", errors);
            fclose(bestword);

            break;
        case 8:
            /*
            playRoutine();

            char** dict = getDictionary();
            int dictSize = getDictionarySize();

            clock_t begin;
            clock_t end;
            char* botWord;

            begin = clock();
            botWord = getBestWordWithEntropy(wordSize, dict, dictSize);
            end = clock();

            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

            printf("%f, %s", time_spent, botWord);
            */
            // permet de trouver quel mot est boosté par l'algo entropy cassé
            // tetee avec +11,75 par rapport à l'entropy fonctionnelle
            // char* wordtofind;
            /*float diff = 0;


            for (int wordIdx = 0; wordIdx < getDictionarySize(); wordIdx++) { // for every word in the dictionnary

                char* word = getDictionary()[wordIdx];

                float entropy = computeEntropy(word, 5, getDictionary(), getDictionarySize());
                float entropybro = computeEntropy_broken(word, 5, getDictionary(), getDictionarySize());

                diff += fabs(entropybro - entropy);
                if (fabs(entropybro - entropy) > diff) {
                    wordtofind = word;
                    diff = fabs(entropybro - entropy);
                }
                //printf("%s :\t\t%.2f %.2f | %.2f\n", word, entropy, entropybro, fabs(entropybro - entropy));
            }

            printf("%f\n", diff/dictSize);*/

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

            /*char* word = "tetee";

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
                        printCharInColor(verif[j], word[j]);
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

            if (!match)
            {
                // go to the end of the stream
                char t[1];
                fscanf(stdin, "%s", t);
            }
            break;
        }
    }

    return 0;
}