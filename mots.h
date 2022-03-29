#ifndef MOTS_H_   /* Include guard */
#define MOTS_H_



int loadDict(char* filepath, int wordSize);

int searchDict(char* word);

char* randomWord();

int* verifyWord(char* toFind, char* userWord);


#endif // MOTS_H_