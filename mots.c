#include <stdio.h>
#include <stddef.h>


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
        printf("Erro: could not open file %s", filepath);
    }

    // save in a ordered struct 

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
    // make something quick
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
