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

extern const int EOF = -2;
extern const int ERROR = -1;
extern const int IGNORE = 0;
extern const int ADD = 1;
extern const int CHECK = 2;
extern const int DELETE = 3;
extern const int PRINT = 4;

extern struct Instruction;

typedef struct Instruction* InstructionPtr;

extern InstructionPtr parseInstruction();

#endif