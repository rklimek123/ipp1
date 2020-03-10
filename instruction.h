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

#define ERROR -2
//#define EOF -1
#define IGNORE 0
#define ADD 1
#define CHECK 2
#define DELETE 3
#define PRINT 4

struct Instruction {
    int command;
    char **forest;
    char **tree;
    char **animal;
};

typedef struct Instruction* InstructionPtr;

//Instruction destructor.
void deleteInstruction(InstructionPtr);

//Reads line from stdin and parses it to Instruction. Returns an InstructionPtr.
//In case of EOF, returns a blank Instruction with EOF command.
InstructionPtr parseInstruction();

#endif /* INSTRUCTION_H */