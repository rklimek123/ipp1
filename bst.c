#include "bst.h"

Tree createTree(char* value, Tree corresponding, Tree left, Tree right) {
    Tree newTree;

    newTree = (Tree)malloc(sizeof(struct Node));
    validateAlloc(newTree);
    
    newTree->value = value;
    newTree->corresponding = corresponding;
    newTree->left = left;
    newTree->right = right;
    
    return newTree;
}

Tree insertAndFind(Tree *treePtr, char *value, bool *inserted) {
    Tree t = *treePtr;

    if (t == NULL) {
        t = createTree(value, NULL, NULL, NULL);

        *treePtr = t;
        *inserted = true;
        
        return *treePtr;
    }
    else if (strcmp(t->value, value) < 0) {
        return insertAndFind(&t->right, value, inserted);
    }
    else if (strcmp(t->value, value) > 0) {
        return insertAndFind(&t->left, value, inserted);
    }
    else {
        *inserted = false;

        return *treePtr;
    }
}

void removeTree(Tree t) {
    if (t != NULL) {
        removeTree(t->left);
        removeTree(t->corresponding);
        removeTree(t->right);

        free(t->value);
        free(t);
    }
}

// Free the value and corresponding of the root of Tree t from memory.
static void removeValueAndCorresponding(Tree t) {
    if (t != NULL) {
        removeTree(t->corresponding);
        t->corresponding = NULL;

        free(t->value);
        t->value = NULL;
    }
}

// Remove the Node with the least value
// (lexicographically, according to extended ASCII sign values)
// and return a Tree with this Node as its root
// (in other words, return a pointer to this Node).
static Tree removeMin(Tree *treePtr) {
    Tree t = *treePtr;

    if (t == NULL) {
        return NULL;
    }
    else {
        if (t->left == NULL) {
            *treePtr = t->right;

            return t;
        }
        else {
            return removeMin(&t->left);
        }
    }
}

void removeElement(Tree *treePtr, char *value) {
    Tree t = *treePtr;
    if (t != NULL) {
        if (strcmp(t->value, value) < 0) {
            removeElement(&t->right, value);
        }
        else if (strcmp(t->value, value) > 0) {
            removeElement(&t->left, value);
        }
        else {
            if (t->right == NULL) {
                *treePtr = t->left;

                removeValueAndCorresponding(t);
                free(t);
            }
            else {
                Tree removedMin = removeMin(&t->right);
                
                removeValueAndCorresponding(t);
                t->corresponding = removedMin->corresponding;
                t->value = removedMin->value;

                free(removedMin);

                *treePtr = t;
            }
        }
    }
}

void printTree(Tree t) {
    if (t != NULL) {
        printTree(t->left);

        printf("%s\n", t->value);
        
        printTree(t->right);
    }
}

Tree findTree(Tree t, char *value) {
    if (t == NULL) {
        return NULL;
    }

    if (strcmp(t->value, value) < 0) {
        return findTree(t->right, value);
    }
    else if (strcmp(t->value, value) > 0) {
        return findTree(t->left, value);
    }
    else {
        return t;
    }
}

Tree *findTreePtr(Tree *treePtr, char *value) {
    Tree t = *treePtr;
    if (t == NULL) {
        return NULL;
    }

    if (strcmp(t->value, value) < 0) {
        return findTreePtr(&t->right, value);
    }
    else if (strcmp(t->value, value) > 0) {
        return findTreePtr(&t->left, value);
    }
    else {
        return treePtr;
    }
}
