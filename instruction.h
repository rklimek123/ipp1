#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#ifndef _STDIO_H
#include <stdio.h>
#endif /* _STDIO_H */

#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* _STDLIB_H */

#ifndef _STRING_H
#include <string.h>
#endif /* _STRING_H */

#ifndef ALLOC_H
#include "alloc.h"
#endif /* ALLOC_H */

#ifndef STRINGOPS_H
#include "stringops.h"
#endif /* STRINGOPS_H */

// Auxiliary definitions, helping managing the command record in Instruction.
#define ERROR -2
// #define EOF -1
#define IGNORE 0
#define ADD 1
#define CHECK 2
#define DEL 3
#define PRINT 4


// Type representing a line of instruction in an organised way.
// command - number representing one of the commands: ADD, CHECK, DELETE, PRINT,
//           but also auxiliary commands: ERROR, EOF, IGNORE.
// forest, tree and animal represent further words in a line of the instruction.
struct Instruction {
    int command;
    char *forest;
    char *tree;
    char *animal;
};


typedef struct Instruction* InstructionPtr;


// Create a new Instruction using given arguments and return a pointer to it.
// 
// Function's arguments correspond to struct Instruction's records.
InstructionPtr createInstruction(int command,
                                char *forest, char *tree, char *animal);


// Free selected strings from Instruction pointed by instructionPtr from memory.
// If clearForest is true, free instructionPtr->forest, etc.
// The freed char pointers are changed to NULL.
void clearInstruction(InstructionPtr instructionPtr, bool clearForest,
                                       bool clearTree, bool clearAnimal);


// Free the Instruction from the memory, as well as all of char pointers in it.
void deleteInstruction(InstructionPtr deleteThisInstructionPtr);


// Read a line from stdin and parse it into the struct Instruction,
// to which instructionPtr points. 
// In case of EOF, parse a blank Instruction with EOF as its command.
// buffer and bufferSize are arguments used by the getline function used inside.
void parseInstruction(InstructionPtr instructionPtr,
                      char **buffer, size_t *bufferSize);


#endif /* INSTRUCTION_H */
