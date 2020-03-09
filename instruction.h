#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef ALLOC_H
    #include "alloc.h"
#endif

#ifndef STRINGOPS_H
    #include "stringops.h"
#endif

extern const int ERROR = -2;
extern const int IGNORE = 0;
extern const int ADD = 1;
extern const int CHECK = 2;
extern const int DELETE = 3;
extern const int PRINT = 4;

struct Instruction {
    int command;
    char **forest;
    char **tree;
    char **animal;
};

extern struct Instruction;

typedef struct Instruction* InstructionPtr;

//Instruction destructor.
extern void deleteInstruction(InstructionPtr);

//Reads line from stdin and parses it to Instruction. Returns an InstructionPtr.
//In case of EOF, returns a blank Instruction with EOF command.
extern InstructionPtr parseInstruction();

#endif