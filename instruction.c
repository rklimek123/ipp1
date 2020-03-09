#include <stdlib.h>
#include "alloc.h"
#include "stringops.h"

const int ERROR = -2;
const int EOF = -1;
const int IGNORE = 0;
const int ADD = 1;
const int CHECK = 2;
const int DELETE = 3;
const int PRINT = 4;

struct Instruction {
    int command;
    char **forest;
    char **tree;
    char **animal;
};

typedef struct Instruction* InstructionPtr;

//Instruction constructor. Returns a pointer.
InstructionPtr createInstruction(int command, char **forest,
                                 char **tree, char **animal) {
    InstructionPtr instructionPtr;
    instructionPtr = (InstructionPtr)malloc(sizeof(struct Instruction));
    validateAlloc(instructionPtr);

    instructionPtr->command = command;
    instructionPtr->forest = forest;
    instructionPtr->tree = tree;
    instructionPtr->animal = animal;
    
    return instructionPtr;
}

//Instruction destructor.
void deleteInstruction(InstructionPtr instructionPtr) {
    free(*(instructionPtr->forest));
    free(*(instructionPtr->tree));
    free(*(instructionPtr->animal));
    free(instructionPtr);
}

//Returns a number indicating the type of command given by the received string.
int translateCommandStr(char *commandStr) {
    char *add = "ADD";
    char *check = "CHECK";
    char *delete = "DELETE";
    char *print = "PRINT";

    if (strcmp(commandStr, add) == 0) return ADD;
    if (strcmp(commandStr, check) == 0) return CHECK;
    if (strcmp(commandStr, delete) == 0) return DELETE;
    if (strcmp(commandStr, print) == 0) return PRINT;
    return ERROR;
}

//Returns an InstructionPtr, pointing at an Instruction with only a command.
InstructionPtr blankInstruction(int command) {
    char **forest;
    char **tree;
    char **animal;

    *forest = NULL;
    *tree = NULL;
    *animal = NULL;

    return createInstruction(command, forest, tree, animal);
}

//Reads line from stdin and parses it to Instruction. Returns an InstructionPtr.
//In case of EOF, returns a blank Instruction with EOF command.
InstructionPtr parseInstruction() {
    int command;
    char **commandStr;
    char **forest;
    char **tree;
    char **animal;
    char **currentLine;

    currentLine = readLine();
    char *instructionStr = *currentLine;
    
    //returns EOF if nothing has been scanned
    if (instructionStr == NULL) {
        free(currentLine);
        return blankInstruction(EOF);
    }
    
    //ignoring lines starting with a '#'
    if (*instructionStr == '#') {
        free(currentLine);
        return blankInstruction(IGNORE);
    }

    instructionStr = removeWhitespaces(instructionStr);
    
    //ignoring empty or blank lines
    if (*instructionStr == '\n') {
        free(currentLine);
        return blankInstruction(IGNORE);
    }

    instructionStr = removeWord(instructionStr, commandStr);
    
    command = translateCommandStr(*commandStr);
    free(*commandStr);

    //returns error immediately if returned to command
    if (command == ERROR) {
        free(currentLine);
        return blankInstruction(ERROR);
    }

    instructionStr = removeWhitespaces(instructionStr);
    instructionStr = removeWord(instructionStr, forest);

    instructionStr = removeWhitespaces(instructionStr);
    instructionStr = removeWord(instructionStr, tree);

    instructionStr = removeWhitespaces(instructionStr);
    instructionStr = removeWord(instructionStr, animal);

    instructionStr = removeWhitespaces(instructionStr);

    //returns error if there are still some signs in a line
    if (*instructionStr != '\n'){
        free(*currentLine);
        free(*forest);//tutaj przypisuje adres gdzies tam a potem usuwam stad lol? moze lepiej jakies kopie? jest chyba na to jakiś modulik. Valgrind poleca
        free(*tree);
        free(*animal);
        return blankInstruction(ERROR);
    }

    return createInstruction(command, forest, tree, animal);
}

int main() {
    return 0;
}