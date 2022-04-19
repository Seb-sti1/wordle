#ifndef WORD_H_   /* Include guard */
#define WORD_H_

int getDictionarySize();

char** getDictionary();

void destroyDictonary();

int loadDict(char* filepath, int wordSize);

int searchDict(char* word);

char* randomWord();

int* verifyWord(char* toFind, char* userWord);


#endif // WORD_H_