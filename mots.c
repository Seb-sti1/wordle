#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "mots.h"

// the dict
char* dictionary[110000];
int size=110000;


/**
 * Load the dict into a global static variable
 * 
 * 
 * arg:
 * char* filepath : file path
 * 
 * return: 
 * int (bool) success
 * 
 * 
 */
int loadDict(char* filepath)
{
    // load file

    FILE *dico = fopen(filepath, "r");

    if (dico == NULL) {
        printf("Error: could not open file %s", filepath);
    }

    int i = 0;

    // save the data 
    while (!feof(dico)) {
        char* temp = malloc(sizeof(char*)*32);

        int ret = fscanf("%s\n", &temp);
        dictionary[i] = temp;

        i++;
    }
    size = i;

    fclose(dico);
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
        int middle = (end - front)/2;

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
    // choose a random word

}