#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "mots.h"

// the dict
int size=50000;
char* dictionary[50000];


/**
 * Load the dict into a global static variable
 * 
 * 
 * arg:
 * char* filepath : file path
 * int wordSize : the size of the word
 * 
 * return: 
 * int (bool) success
 * 
 * 
 */
int loadDict(char* filepath, int wordSize)
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
    size = i;

    fclose(dico);

    return true;
}

/**
 * Search a word in the dictonary
 * 
 * arg:
 * char* word : the word to search
 * 
 * return:
 * int (bool) found 
 * 
 */
int searchDict(char* word)
{
    int front = 0;
    int end = size;

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


/**
 * Search for a random word
 * 
 * return:
 * a random word
 * 
 */
char* randomWord()
{
    srand(time(NULL)); // reset random seed

  	//method to derive a random number
  	int n = rand() % (size + 1);

  	return dictionary[n];
}




/**
 * Verify word
 * 
 * arg :
 * char* toFind : the word to find
 * char* userWord : the word given by the user
 * 
 * return:
 * a table of int : 0 = char are the same, 1 = char are different, 2 = misposed
 * 
 * 
 */
int* verifyWord(char* toFind, char* userWord) {

    int wordSize = strlen(toFind);

    // create a 0 array
    int* usedChar = malloc(sizeof(int)*wordSize);
    for (int i = 0; i < wordSize; i++) {
        usedChar[i] = 0;
    }

    int* verifTable = malloc(sizeof(int)*wordSize);

    // find char that are identical
    for (int i = 0; i < wordSize; i++) {
        verifTable[i] = 1; // by default the char considered as different

        if (userWord[i] == toFind[i]) { // if the char are the same
            verifTable[i] = 0;

            usedChar[i] = 1; // mark the char as used
        }
    }


    // find char misposed char
    for (int i = 0; i < wordSize; i++) {
        for (int j = 0; j < wordSize; j++) {
            if (!usedChar[j]) { // if the char isn't used
                if (userWord[i] == toFind[j]) { // if the char are the same
                    verifTable[i] = 2; // then the char is just misposed

                    usedChar[j] = 1; // mark the char as used
                }
            }
        }
        
    }

    return verifTable;
}