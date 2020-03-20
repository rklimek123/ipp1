#include "instruction.h"

InstructionPtr createInstruction(int command,
                                char *forest, char *tree, char *animal) {
                                     
    InstructionPtr instructionPtr = (InstructionPtr)malloc(sizeof(struct Instruction));

    instructionPtr->command = command;
    instructionPtr->forest = forest;
    instructionPtr->tree = tree;
    instructionPtr->animal = animal;

    return instructionPtr;
}

void clearInstruction(InstructionPtr instructionPtr, bool clearForest,
                                       bool clearTree, bool clearAnimal) {

    if(instructionPtr->forest != NULL && clearForest) {
        free(instructionPtr->forest);
        instructionPtr->forest = NULL;
    }
    if(instructionPtr->tree != NULL && clearTree) {
        free(instructionPtr->tree);
        instructionPtr->tree = NULL;
    }
    if(instructionPtr->animal != NULL && clearAnimal) {
        free(instructionPtr->animal);
        instructionPtr->animal = NULL;
    }
}

void deleteInstruction(InstructionPtr instructionPtr) {
    clearInstruction(instructionPtr, true, true, true);
    free(instructionPtr);
}

// Return a number indicating the type of command given by the received string.
// Return ERROR if the commandStr doesn't match any of the commands.
static int translateCommandStr(char *commandStr) {
    if (strcmp(commandStr, "ADD") == 0) return ADD;
    if (strcmp(commandStr, "CHECK") == 0) return CHECK;
    if (strcmp(commandStr, "DEL") == 0) return DEL;
    if (strcmp(commandStr, "PRINT") == 0) return PRINT;
    return ERROR;
}

// Change values in Instruction pointed by instructionPtr, to the ones given
// by the function's arguments.
// 
// WARNING: Doesn't free previously present char* records from memory.
static void changeInstruction(InstructionPtr instructionPtr, int command,
                              char *forest, char *tree, char *animal) {
    
    instructionPtr->command = command;
    instructionPtr->forest = forest;
    instructionPtr->tree = tree;
    instructionPtr->animal = animal;
}

// Change the Instruction pointed by instructionPtr
// to have only the given command.
static void blankInstruction(InstructionPtr instructionPtr, int command) {
    changeInstruction(instructionPtr, command, NULL, NULL, NULL);
}

void parseInstruction(InstructionPtr instructionPtr, 
                                char **buffer, size_t *bufferSize) {

    int charsRead = getline(buffer, bufferSize, stdin);

    char *instructionStr = *buffer;
    
    // return EOF if nothing has been scanned
    if (charsRead < 1) {
        blankInstruction(instructionPtr, EOF);
        return;
    }

    // IGNORE empty lines (e.g. "\n")
    if (charsRead == 1) {
        blankInstruction(instructionPtr, IGNORE);
        return;
    }
    
    // IGNORE lines starting with a '#'
    if (*instructionStr == '#') {
        blankInstruction(instructionPtr, IGNORE);
        return;
    }

    instructionStr = removeWhitespaces(instructionStr);
    
    // IGNORE lines made solely of whitespaces,
    // also when they are at the end of the file.
    if (*instructionStr == '\n' || *instructionStr == '\0') {
        blankInstruction(instructionPtr, IGNORE);
        return;
    }
    
    int command;
    char *commandStr = (char *)malloc(sizeof(char));

    instructionStr = removeWord(instructionStr, &commandStr);
    
    command = translateCommandStr(commandStr);
    free(commandStr);

    // return ERROR immediately if command is not valid
    if (command == ERROR) {
        blankInstruction(instructionPtr, ERROR);
        return;
    }

    char *forest = (char *)malloc(sizeof(char));
    char *tree = (char *)malloc(sizeof(char));
    char *animal = (char *)malloc(sizeof(char));

    instructionStr = removeWhitespaces(instructionStr);
    instructionStr = removeWord(instructionStr, &forest);

    instructionStr = removeWhitespaces(instructionStr);
    instructionStr = removeWord(instructionStr, &tree);

    instructionStr = removeWhitespaces(instructionStr);
    instructionStr = removeWord(instructionStr, &animal);

    instructionStr = removeWhitespaces(instructionStr);

    // return ERROR if there are still some signs in a line
    if (*instructionStr != '\n'){
        free(forest);
        free(tree);
        free(animal);
        blankInstruction(instructionPtr, ERROR);
        return;
    }

    changeInstruction(instructionPtr, command, forest, tree, animal);
}
