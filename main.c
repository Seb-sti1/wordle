#include <stdio.h>


int main(int argc, char const *argv[])
{
    int tries = 0;

    loadDict("./liste_complete_triee.txt");

    char* mot = malloc(sizeof(char*)*32);

    fscanf(stdin, "%s\n", &mot);

    searchDict(mot);

    // choose a random word

    while (tries < 6) {

        // ask word

        // check for word in dict

        // if everything ok
            // compare with the words
                // if its the same -> You win
                // else print the differences

    }

    // if too many tries -> you lose
    
    return 0;
}



/**
 * ask for a string of 5 char
 * 
 * return : char* a string of 5 char or NULL (on error)
 * 
 */
char* askWord()
{



}