#include <stdbool.h>
#include <stdio.h>
#include "bst.h"
#include "instruction.h"

bool isForest(struct Instruction instruction) {
    if (*(instruction.forest) == NULL) {
        return false;
    }
    return true;
}

bool isTree(struct Instruction instruction) {
    if (*(instruction.tree) == NULL) {
        return false;
    }
    return true;
}

bool isAnimal(struct Instruction instruction) {
    if (*(instruction.animal) == NULL) {
        return false;
    }
    return true;
}

void errorResponse() {
    fprintf(stderr, "ERROR\n");
}

void okResponse() {
    fprintf(stdout, "OK\n");
}

void addCommand(Tree *targetTree, struct Instruction instruction) {
    if (!isForest(instruction)) {
        errorResponse();
        return;
    }

    Tree *addThere = NULL;
    *addThere = NULL;

    addThere = insert(targetTree, instruction.forest);

    if (isTree(instruction)) {
        addThere = insert(&((*addThere)->corresponding), instruction.tree);
    }

    if (isAnimal(instruction)) {
        addThere = insert(&((*addThere)->corresponding), instruction.animal);
    }
}

bool validateCheck(struct Instruction instruction) {
    char *lastArgument;
    lastArgument = NULL;
    
    if (isAnimal(instruction)) {
        lastArgument = *(instruction.animal);
    }
    else if (isTree(instruction)) {
        lastArgument = *(instruction.tree);
    }
    else if (isForest(instruction)) {
        lastArgument = *(instruction.forest);
    }
    else {
        return false;
    }

    if (strcmp(lastArgument, "*") == 0) {
        return false;
    }

    return true;
}

#define FOREST 0
#define TREE 1

bool checkInAny(Tree targetTree, struct Instruction instruction, int level) {
    if (targetTree == NULL) {
        return false;
    }

    if (level == FOREST) {
        if (strcmp(*(instruction.tree), "*") == 0) {
            if (checkInAny(targetTree->corresponding, instruction, TREE)) {
                return true;
            }
        }
        else {
            if (*findTree(targetTree->corresponding, *(instruction.tree)) != NULL) {
                return true;
            }
        }
    }
    else { //if (level == TREE)
        if (*findTree(targetTree->corresponding, *(instruction.animal)) != NULL) {
            return true;
        }
    }

    return checkInAny(targetTree->left, instruction, level) ||
           checkInAny(targetTree->right, instruction, level);
}

void checkCommand(Tree *targetTree, struct Instruction instruction) {
    if (!validateCheck(instruction)) {
        errorResponse();
        return;
    }
    
    Tree *checkThere = NULL;
    *checkThere = NULL;

    if (strcmp(*(instruction.forest), "*") == 0) {
        if (checkInAny (*targetTree, instruction, FOREST)){
            printf("YES\n");
        }
    }
    else if (strcmp(*(instruction.tree), "*") == 0){
        if (checkInAny((*findTree(*targetTree, *(instruction.forest)))->corresponding, instruction, TREE)) {
            printf("YES\n");
        }
    }
    else if (*findTree(*targetTree, *(instruction.forest)) != NULL) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}

void deleteCommand(Tree *targetTree, struct Instruction instruction) {
    Tree *deleteThere;
    deleteThere = targetTree;
    
    char *deleteValue;
    deleteValue = NULL;

    if (isForest(instruction)) {
        deleteValue = *(instruction.forest);
        deleteThere = findTree(*deleteThere, deleteValue);
    }
    if (isTree(instruction)) {
        deleteValue = *(instruction.tree);
        deleteThere = findTree((*deleteThere)->corresponding, deleteValue);
    }
    if (isAnimal(instruction)) {
        deleteValue = *(instruction.animal);
        deleteThere = findTree((*deleteThere)->corresponding, deleteValue);
    }

    if (deleteThere != NULL) {
        if (deleteValue == NULL) {
            removeTree (*targetTree);
        }
        else {
            removeElement(deleteThere, deleteValue);
        }
    }
}

void printCommand(Tree *targetTree, struct Instruction instruction) {
    if (isAnimal(instruction)) {
        errorResponse();
        return;
    }

    Tree *printThere;
    printThere = targetTree;

    char *printValue;
    printValue = NULL;
    
    if (isForest(instruction)) {
        printValue = *(instruction.forest);
        printThere = findTree(*printThere, printValue);
    }
    if (isTree(instruction)) {
        printValue = *(instruction.tree);
        printThere = findTree((*printThere)->corresponding, printValue);
    }

    if (!isForest(instruction)) {
        printTree(*printThere);
    }
    else {
        printTree((*printThere)->corresponding);
    }
}

int main() {
    InstructionPtr currentInstruction;
    Tree *forests = NULL;
    *forests = NULL;

    while(true) {
        currentInstruction = parseInstruction();

        if (currentInstruction->command == EOF) {
            deleteInstruction(currentInstruction);
            break;
        }
        else if (currentInstruction->command == ERROR) {
            errorResponse();
        }
        else if (currentInstruction->command == ADD) {
            addCommand(forests, *currentInstruction);
        }
        else if (currentInstruction->command == CHECK) {
            checkCommand(forests, *currentInstruction);
        }
        else if (currentInstruction->command == DELETE) {
            deleteCommand(forests, *currentInstruction);
        }
        else if (currentInstruction->command == PRINT) {
            printCommand(forests, *currentInstruction);
        }

        deleteInstruction(currentInstruction);
    }

    removeTree(*forests);

    return 0;
}