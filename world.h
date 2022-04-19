#ifndef WORLD_H_   /* Include guard */
#define WORLD_H_



int loadDict(char* filepath, int wordSize);

int searchDict(char* word);

char* randomWord();

int* verifyWord(char* toFind, char* userWord);


#endif // WORLD_H_