#include "stringops.h"

// Check if a character is a letter.
// 
// NOTE: A character is a letter if its value in extended ASCII table
//       is 33 or greater.
static bool isLetter(char a) {
    unsigned char ua = (unsigned char)a;
    return ua > 32;
}

// Append a char to a string.
// Double the memory allocated for this string if necessary.
// 
// targetStr       - the string to which a char is going to be appended
// targetStrLength - pointer to the current length of the string
// maxLength       - pointer to the maximum amount of chars in the string,
//                   including the null terminator '\0'.
// addedChar       - a char going to be appended
static void addChar(char *targetStr, size_t *targetStrLength,
                  size_t *maxLength, char addedChar) {
    
    *targetStrLength += 1;
    
    if (*targetStrLength + 1 >= *maxLength) {
        *maxLength *= 2;
        targetStr = (char *)realloc(targetStr, *maxLength * sizeof(char));
        validateAlloc(targetStr);
    }

    *(targetStr + *targetStrLength - 1) = addedChar;
    *(targetStr + *targetStrLength) = '\0';
}

char *removeWord(char *baseStr, char **removedWordLocation) {
    char *removedWord = NULL;

    size_t removedWordLength = 0;
    size_t maxWordLength = 1;
    
    removedWord = (char *)malloc(maxWordLength * sizeof(char));
    validateAlloc(removedWord);
    *removedWord = '\0';

    while (isLetter(*baseStr)) {
        addChar(removedWord, &removedWordLength, &maxWordLength, *baseStr);
        baseStr++;
    }

    removedWord = (char *)realloc(removedWord,
                                 (removedWordLength + 1) * sizeof(char));
    validateAlloc(removedWord);
    
    free(*removedWordLocation);
    *removedWordLocation = removedWord;

    return baseStr;
}

// Check if a character is a whitespace.
// 
// DISCLAIMER: '\n' isn't considered a whitespace.
static bool isWhitespace(char a) {
    return a == ' '  ||
           a == '\t' ||
           a == '\v' ||
           a == '\f' ||
           a == '\r';
}

char *removeWhitespaces(char *baseStr) {
    while (isWhitespace(*baseStr)) {
        baseStr++;
        if (baseStr == NULL) {
            return NULL;
        }
    }

    return baseStr;
}
