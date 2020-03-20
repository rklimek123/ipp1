#include <stdbool.h>
#include <stdio.h>
#include "alloc.h"
#include "bst.h"
#include "instruction.h"

// Check if instruction has a forest.
bool hasForest(struct Instruction instruction) {
    if (instruction.forest == NULL || *instruction.forest == '\0') {
        return false;
    }

    return true;
}

// Check if instruction has a tree.
bool hasTree(struct Instruction instruction) {
    if (instruction.tree == NULL || *instruction.tree == '\0') {
        return false;
    }

    return true;
}

// Check if instruction has a forest.
bool hasAnimal(struct Instruction instruction) {
    if (instruction.animal == NULL || *instruction.animal == '\0') {
        return false;
    }

    return true;
}

// Display "ERROR" onto stderr, followed by a new line sign.
void errorResponse() {
    fprintf(stderr, "ERROR\n");
}

// Display "OK" onto stdout, followed by a new line sign.
void okResponse() {
    printf("OK\n");
}

// Handle an instruction call with an ADD command.
// 
// targetTree     - pointer to a Tree, with forests as its elements.
// instructionPtr - pointer to an Instruction containing information
//                  about values that are going to be added to the Tree.
// 
// Examples:
// ADD a     - adds a forest named a to the Tree.
// 
// ADD a b   - adds a forest named a to the Tree
//             and a tree named b to a->corresponding.
// 
// ADD a b c - adds a forest named a to the Tree,
//             a tree named b to a->corresponding
//             and an animal named c to b->corresponding.
// 
// ADD instruction adds only objects which are not currently present
// in a particular Tree. If an object exists in this Tree, it's not added.
// 
// If no error occured, display "OK" onto stdout, followed by a new line sign.
// Else, display "ERROR" onto stderr, followed by a new line sign.
void addCommand(Tree *targetTree, InstructionPtr instructionPtr) {
    // "ADD" is not a valid instruction (need at least 1 argument)
    if (!hasForest(*instructionPtr)) {
        errorResponse();
        clearInstruction(instructionPtr, true, true, true);
        return;
    }

    Tree addThere = *targetTree;

    bool insertedForest, insertedTree, insertedAnimal;
    insertedForest = false;
    insertedTree = false;
    insertedAnimal = false;

    addThere = insertAndFind(targetTree, instructionPtr->forest, &insertedForest);

    if (hasTree(*instructionPtr)) {
        addThere = insertAndFind(&addThere->corresponding, instructionPtr->tree, &insertedTree);
    }

    if (hasAnimal(*instructionPtr)) {
        addThere = insertAndFind(&addThere->corresponding, instructionPtr->animal, &insertedAnimal);
    }
    
    okResponse();

    // clears char* not inserted to the BST from instruction,
    // prior to further overwriting, which would cause a data leak otherwise
    clearInstruction(instructionPtr,
                     !insertedForest, !insertedTree, !insertedAnimal);
}

// Check if a CHECK instruction is valid.
bool validateCheck(struct Instruction instruction) {
    // "CHECK" is not a valid instruction (need at least 1 argument)
    if (!hasForest(instruction)) {
        return false;
    }

    char *lastArgument = NULL;
    
    if (hasAnimal(instruction)) {
        lastArgument = instruction.animal;
    }
    else if (hasTree(instruction)) {
        lastArgument = instruction.tree;
    }
    else { // if (hasForest(instruction))
        lastArgument = instruction.forest;
    }
    
    // last argument of a CHECK instruction cannot be an asterisk (*)
    if (strcmp(lastArgument, "*") == 0) {
        return false;
    }

    return true;
}

// Auxiliary definitions, helping managing the level argument of checkInAny.
#define FOREST 0
#define TREE 1

// Auxiliary function for checkCommand, handles wildcard (*) arguments.
// 
// targetTree  - Tree in which existence of certain objects is being checked.
// instruction - Instruction containing information about values that are going
//               to be checked.
// level       - on what level of nesting is the function traversing.
//               For example:
//                   level = TREE means: currently checking if for any tree...
bool checkInAny(Tree targetTree, struct Instruction instruction, int level) {
    if (targetTree == NULL) {
        return false;
    }

    // currently checked forest's trees / currently checked tree's animals
    Tree checkThere = targetTree->corresponding;

    if (level == FOREST) {
        if (strcmp(instruction.tree, "*") == 0) {
            if (checkInAny(checkThere, instruction, TREE)) {
                // The searched animal has been found in any tree of any forest
                return true;
            }
        }
        else {
            // finding a tree in currently checked forest
            checkThere = findTree(checkThere, instruction.tree);
            
            if (checkThere != NULL) {
                if (hasAnimal(instruction)) {
                    // found tree's animals
                    checkThere = checkThere->corresponding;

                    // finding an animal in found tree
                    checkThere = findTree(checkThere, instruction.animal);

                    if (checkThere != NULL) {
                        // The searched animal has been found in this tree of any forest
                        return true;
                    }
                }
                else {
                    // The searched tree has been found in any forest
                    return true;
                }
            }
        }
    }
    else { // if (level == TREE)
        // finding an animal in currently checked tree
        checkThere = findTree(checkThere, instruction.animal);

        if (checkThere != NULL) {
            // The searched animal has been found in any tree
            return true;
        }
    }
    
    // If nothing has been found, continue searching.
    return checkInAny(targetTree->left, instruction, level) ||
           checkInAny(targetTree->right, instruction, level);
}

// Handle an instruction call with a CHECK command.
// 
// targetTree     - pointer to a Tree, with forests as its elements.
// instructionPtr - pointer to an Instruction containing information
//                  about values that are going to be checked in the Tree.
// 
// Examples:
// CHECK a     - checks if a forest named a exists in the Tree.
// 
// CHECK a b   - checks if a tree named b exists in a->corresponding,
//               with a being a forest in Tree.
// 
// CHECK a b c - checks if an animal named c exists in b->corresponding,
//               with b being a tree in a->corresponding
//               and c being a forest in Tree.
// 
// Any argument, except of the last one, can be an asterisk (written *),
// which then works as a wildcard, meaning any.
// For example:
//     CHECK * b - checks if a tree named b exists in a corresponing
//                 of any forest in Tree.
//
// If no error occured, display "YES" or "NO" onto stdout,
// followed by a new line sign, according to the check's result.
// Else, display "ERROR" onto stderr, followed by a new line sign.
void checkCommand(Tree targetTree, InstructionPtr instructionPtr) {
    if (!validateCheck(*instructionPtr)) {
        //check invalid
        errorResponse();
        clearInstruction(instructionPtr, true, true, true);
        return;
    }

    Tree checkThere = targetTree;

    if (strcmp(instructionPtr->forest, "*") == 0) {
        // checking in all forests
        if (checkInAny (checkThere, *instructionPtr, FOREST)){
            // Something has been found in any of all forests
            printf("YES\n");
        }
        else {
            // Nothing has been found in any of all forests
            printf("NO\n");
        }
    }
    else {
        // finding forest in Tree
        checkThere = findTree(checkThere, instructionPtr->forest);

        if (checkThere != NULL) {
            if (hasTree(*instructionPtr)) {
                // trees of found forest
                checkThere = checkThere->corresponding;

                if (strcmp(instructionPtr->tree, "*") == 0) {
                    if (checkInAny(checkThere, *instructionPtr, TREE)) {
                        // The searched animal has been found in any of these trees
                        printf("YES\n");
                    }
                    else {
                        // The searched animal hasn't been found in any of these trees
                        printf("NO\n");
                    }
                }
                else {
                    // finding tree in forest->corresponding
                    checkThere = findTree(checkThere, instructionPtr->tree);

                    if (checkThere != NULL) {
                        if (hasAnimal(*instructionPtr)) {
                            // animals of found tree
                            checkThere = checkThere->corresponding;

                            // finding animal in tree->corresponding
                            checkThere = findTree(checkThere, instructionPtr->animal);

                            if (checkThere != NULL) {
                                // The searched animal has been found in this tree
                                printf("YES\n");
                            }
                            else {
                                // The searched animal hasn't been found in this tree
                                printf("NO\n");
                            }
                        }
                        else {
                            // The searched tree has been found in this forest
                            printf("YES\n");
                        }
                    }
                    else {
                        // The searcher tree hasn't been found in this forest
                        printf("NO\n");
                    }
                }
            }
            else {
                // The searched forest has been found in all forests
                printf("YES\n");
            }
        }
        else {
            // The searched forest hasn't been found in Tree
            printf("NO\n");
        }
    }

    clearInstruction(instructionPtr, true, true, true);
}

// Handle an instruction call with a DEL command.
// 
// targetTree     - pointer to a Tree, with forests as its elements.
// instructionPtr - pointer to an Instruction containing information
//                  about values that are going to be deleted from the Tree.
// 
// Examples:
// DEL       - deletes all forests in the Tree,
//             all trees in correspondings of every deleted forest
//             and all animals in correspondings of every deleted tree.
// 
// DEL a     - deletes a forest named a from the Tree,
//             all trees in a->corresponding
//             and all animals in correspondings of every deleted tree.
// 
// DEL a b   - deletes a tree named b from a->corresponding
//             as well as all animals in b->corresponding,
//             with a being a forest in Tree.
// 
// DEL a b c - deletes an animal named c from b->corresponding,
//             with b being a tree in a->corresponding
//             and a being a forest in Tree.
// 
// DEL instruction deletes only objects which exist in a particular Tree.
// If an object doesn't exist in this Tree, it's not deleted.
// 
// If no error occured, display "OK" onto stdout, followed by a new line sign.
// Else, display "ERROR" onto stderr, followed by a new line sign.
void delCommand(Tree *targetTree, InstructionPtr instructionPtr) {
    Tree *delThere = targetTree;
    char *delValue = NULL;

    if (hasForest(*instructionPtr)) {
        delValue = instructionPtr->forest;

        // finding a forest in *targetTree
        delThere = findTreePtr(delThere, delValue);
        
        if (delThere == NULL) {
            // no deletion, because the forest hasn't been found
            okResponse();
            clearInstruction(instructionPtr, true, true, true);
            return;
        }
    }
    if (hasTree(*instructionPtr)) {
        delValue = instructionPtr->tree;

        // finding a tree in the forest->corresponding
        delThere = findTreePtr(&(*delThere)->corresponding, delValue);
        
        if (delThere == NULL) {
            // no deletion, because the forest hasn't been found
            okResponse();
            clearInstruction(instructionPtr, true, true, true);
            return;
        }
        
    }
    if (hasAnimal(*instructionPtr)) {
        delValue = instructionPtr->animal;
        // finding an animal in the tree->corresponding
        delThere = findTreePtr(&(*delThere)->corresponding, delValue); // found animal
    }
    
    // if an animal has been found
    if (delThere != NULL) {
        if (delValue == NULL) {
            // in case of "DEL" instruction, with no arguments, delete it whole
            removeTree(*targetTree);
            *targetTree = NULL;
        }
        else {
            //delete found element
            removeElement(delThere, delValue);
        }
    }

    okResponse();
    clearInstruction(instructionPtr, true, true, true);
}

// Handle an instruction call with a PRINT command.
//
// targetTree     - pointer to a Tree, with forests as its elements.
// instructionPtr - pointer to an Instruction containing information
//                  about values that are going to be printed from the Tree.
// 
// Examples:
// PRINT     - prints all forests in the Tree,
// 
// PRINT a   - prints all trees in a->corresponding,
//             with a being a forest in Tree.
// 
// PRINT a b - prints all animals in b->corresponding,
//             with b being a tree in a->corresponding
//             and a being a forest in Tree.
// 
// PRINT instruction prints objects sorted lexicographically, ascending,
// according to the values in extended ASCII table, all in separate lines.
// Doesn't do anything if there are no objects to be printed.
// 
// If error occured, display "ERROR" onto stderr, followed by a new line sign.
void printCommand(Tree targetTree, InstructionPtr instructionPtr) {
    // "PRINT a b c" is not a valid instruction (too many arguments)
    if (hasAnimal(*instructionPtr)) {
        errorResponse();
        clearInstruction(instructionPtr, true, true, true);
        return;
    }

    Tree printThere = targetTree;
    char *printValue = NULL;
    
    if (hasForest(*instructionPtr)) {
        printValue = instructionPtr->forest;

        // finding a forest in targetTree
        printThere = findTree(printThere, printValue);
        
        if (printThere == NULL) {
            // no printing, because the forest hasn't been found
            clearInstruction(instructionPtr, true, true, true);
            return;
        }
        
        // going to print all of trees in forest->corresponding
        printThere = printThere->corresponding;
    }
    if (hasTree(*instructionPtr)) {
        printValue = instructionPtr->tree;

        // finding a tree in forest->corresponding
        printThere = findTree(printThere, printValue);
        
        if (printThere == NULL) {
            // no printing, because the tree hasn't been found
            clearInstruction(instructionPtr, true, true, true);
            return;
        }
        
        // going to print all of animals in tree->corresponding
        printThere = printThere->corresponding;
    }
    
    printTree(printThere);
    
    clearInstruction(instructionPtr, true, true, true);
}

int main() {
    Tree *forests = (Tree *)malloc(sizeof(Tree));
    *forests = NULL;

    size_t bufferSize = 32;
    char *buffer = (char *)malloc(bufferSize * sizeof(char));
    validateAlloc(buffer);
    
    InstructionPtr currentInstruction = createInstruction(IGNORE, NULL, NULL, NULL);

    while (true) {
        parseInstruction(currentInstruction, &buffer, &bufferSize);

        if (currentInstruction->command == EOF) {
            break;
        }
        else if (currentInstruction->command == ERROR) {
            errorResponse();
            clearInstruction(currentInstruction, true, true, true);
        }
        else if (currentInstruction->command == ADD) {
            addCommand(forests, currentInstruction);
        }
        else if (currentInstruction->command == CHECK) {
            checkCommand(*forests, currentInstruction);
        }
        else if (currentInstruction->command == DEL) {
            delCommand(forests, currentInstruction);
        }
        else if (currentInstruction->command == PRINT) {
            printCommand(*forests, currentInstruction);
        }
        else {
            clearInstruction(currentInstruction, true, true, true);
        }
    }

    removeTree(*forests);
    free(forests);
    deleteInstruction(currentInstruction);
    free(buffer);
    return 0;
}
