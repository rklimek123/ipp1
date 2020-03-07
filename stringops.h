#ifndef STRINGOPS_H
#define STRINGOPS_H

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _STRING_H
    #include <string.h>
#endif

#ifndef ALLOC_H
    #include "alloc.h"
#endif

//Returns a string without whitespaces at the beginning.
extern char *removeWhitespaces(char *);

//Returns a string after a word has been removed.
//The removed word goes to a target location.
extern char *removeWord(char *, char **);

//Returns pointer to a string with a line, taken from stdin. Ends with '\n'.
extern char **readLine();

#endif