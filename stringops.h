#ifndef STRINGOPS_H
#define STRINGOPS_H

#ifndef _STDBOOL_H
#include <stdbool.h>
#endif /* _STDBOOL_H */

#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* _STDLIB_H */

#ifndef ALLOC_H
#include "alloc.h"
#endif /* ALLOC_H */


// Return a char* similar to baseStr, but without letters at the beginning.
// The resulting pointer points to the first non-letter sign of baseStr.
// 
// Additionally, removedWordLocation becomes a pointer to the removed word.
// 
// NOTE: A character is a letter if its value in extended ASCII table
//       is 33 or greater.
// 
// DISCLAIMER: removedWordLocation cannot be a NULL pointer.
char *removeWord(char *baseStr, char **removedWordLocation);


// Return a char* similar to baseStr, but without whitespaces at the beginning.
// The resulting pointer points to the first non-whitespace sign of baseStr.
// 
// DISCLAIMER: '\n' isn't considered a whitespace.
char *removeWhitespaces(char *baseStr);


#endif /* STRINGOPS_H */
