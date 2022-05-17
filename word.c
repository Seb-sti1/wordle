#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "word.h"

// the dict
int dictSize=50000;
char* dictionary[50000];

int getDictionarySize() {
    return dictSize;
}

char** getDictionary() {
    return dictionary;
}

bool loadDict(char* filepath, int wordSize)
{
    // load file

    FILE *dico = fopen(filepath, "r");

    if (dico == NULL) {
        printf("Error: could not open file %s", filepath);
        return false;
    }

    int i = 0;

    // save the data 
    while (!feof(dico)) {
        char* temp = malloc(sizeof(char)*32);

        int ret = fscanf(dico, "%s\n", temp);

        if (ret != 1) {
            printf("Un mot n'a pas pu être chargé...");
        } else {
            if (strlen(temp) == wordSize) {
                dictionary[i] = temp;
                i++;
            }
        }
    }
    dictSize = i;

    fclose(dico);

    return true;
}

void destroyDictonary() {
    for (int i = 0; i < dictSize; i++) {
        free(dictionary[i]);
    }
}

bool searchDict(char* word)
{
    int front = 0;
    int end = dictSize;

    while (end - front > 1) {
        int middle = (end + front)/2;

        int order = strcmp(word, dictionary[middle]);

        if (order == 0) { // if found
            return true;
        } else if (order < 0) {//word < dictionary[middle]
            end = middle;
        } else {// word > dictionary[middle]
            front = middle;
        }
    }


    return strcmp(word, dictionary[front]) == 0 || strcmp(word, dictionary[end]) == 0;
}


char* randomWord()
{
    srand(time(NULL)); // reset random seed

  	//method to derive a random number
  	int n = rand() % (dictSize + 1);

  	return dictionary[n];
}

int* verifyWord(char* toFind, char* userWord) {
    int wordSize = strlen(toFind);
    

    // identify char that are already assined
    int usedCharToFind[wordSize];
    for (int i = 0; i < wordSize; i++) {
        usedCharToFind[i] = 0;
    }

    int usedCharUserWord[wordSize];
    for (int i = 0; i < wordSize; i++) {
        usedCharUserWord[i] = 0;
    }

    
    int* verifTable = malloc(sizeof(int)*wordSize);



    // find char that are identical
    for (int i = 0; i < wordSize; i++) {
        verifTable[i] = 1; // by default the char considered as different

        if (userWord[i] == toFind[i]) { // if the char are the same
            verifTable[i] = 0;

            usedCharToFind[i] = 1;
            usedCharUserWord[i] = 1;
        }
    }


    // find char misposed char
    for (int i = 0; i < wordSize; i++) {
        for (int j = 0; j < wordSize; j++) {
            if (!usedCharUserWord[i]) { // if the char hasn't been mark
                if (!usedCharToFind[j]) { // if the char hasn't been mark
                    if (userWord[i] == toFind[j]) { // if the char are the same 
                        verifTable[i] = 2; // then the char is just misposed

                        usedCharUserWord[i] = 1;
                        usedCharToFind[j] = 1;
                    }
                }
            }
        }
        
    }

    return verifTable;
}