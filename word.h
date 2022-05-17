#ifndef WORD_H_   /* Include guard */
#define WORD_H_

/**
 * @brief Get the dictionary size
 * 
 * @return int the number of word in the dictionary
 */
int getDictionarySize();

/**
 * @brief Get the dictionary
 * 
 * @return char** the dictionary
 */
char** getDictionary();

/**
 * @brief free every words inthe dictionary
 */
void destroyDictonary();

/**
 * @brief load the word from a file into a array
 * 
 * @param filepath the path to the dictionary
 * @param wordSize the size of word
 * @return int 
 */
bool loadDict(char* filepath, int wordSize);

/**
 * @brief Search a word in the dictonary
 * 
 * @param word the word to search
 * @return bool if the word is in the dictonary 
 */
bool searchDict(char* word);

/**
 * @brief choose a random word
 * 
 * @return char* a random word
 */
char* randomWord();


/**
 * @brief verify a word
 * 
 * @param toFind : the word to find
 * @param userWord : the word given by the user
 * @return int* the pattern 0 = char are the same, 1 = char are different, 2 = misposed
 */
int* verifyWord(char* toFind, char* userWord);


#endif // WORD_H_