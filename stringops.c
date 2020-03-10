#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "alloc.h"
#include "stringops.h"

//Checks if a character is a whitespace.
static bool isWhitespace(char a) {
    a == ' ' || a == '\t' || a == '\v' || a == '\f' || a == '\r';
}

//Checks if a character is a letter.
static bool isLetter(char a) {
    a > 32 || a < 0;
}

//Returns a string without whitespaces at the beginning.
char *removeWhitespaces(char *baseStr) {
    while (isWhitespace(*baseStr)) {
        baseStr++;
        if (baseStr == NULL) return NULL;
    }
    return baseStr;
}

//Adds a char to a string;
static void addChar(char **targetStr, unsigned long long *targetStrLength,
             unsigned long long *maxLength, char addedChar) {
    if (*targetStrLength + 1 == *maxLength) {
        *maxLength *= 2;
        reallocateAndValidateStr(targetStr, *maxLength);
    }
    *(*targetStr + *targetStrLength) = addedChar;
}

//Returns a string after a word has been removed.
//The removed word goes to a target location.
char *removeWord(char *baseStr, char **removedWordLocation) {
    char *removedWord;
    unsigned int removedWordLength;
    unsigned int maxWordLength;

    removedWordLength = 0;
    maxWordLength = 1;
    allocateAndValidateStr(&removedWord, maxWordLength);

    while (isLetter(*baseStr)) {
        addChar(removedWord, &removedWordLength, &maxWordLength, *baseStr);
        baseStr++;
    }

    reallocateAndValidateStr(&removedWord, removedWordLength + 1);

    *(removedWord + removedWordLength) = '\0';
    *removedWordLocation = removedWord;
    return baseStr;
}

//Returns pointer to a string with a line, taken from stdin. Ends with '\n'.
char **readLine() {
    char *buffer;
    int bufferLength = 0;
    int bufferMaxLength = 1;

    buffer = (char *)malloc(bufferMaxLength * sizeof(char));
    validateAlloc(buffer);

    while (scanf("%d", buffer + bufferLength) == 1 &&
          *(buffer + bufferLength) != '\n') {
        
        bufferLength++;
        
        if (bufferLength == bufferMaxLength) {
            bufferMaxLength *= 2;
            reallocateAndValidateStr(&buffer, bufferMaxLength);
        }
    }

    return &buffer;
}
