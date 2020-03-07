#ifndef ALLOC_H
#define ALLOC_H

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

//Validates if memory has been successfully allocated to a pointer.
extern void validateAlloc (void *);

//Allocate memory for a string to a given pointer and validate allocation.
extern void allocateAndValidateStr(char **, int);

//Reallocate memory for a string to a certain length and validate allocation.
extern void reallocateAndValidateStr(char **, int);

#endif