#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc.h"
#include "bst.h"

Tree createTree(char** value, Tree corresponding, Tree left, Tree right) {
    Tree n;
    n = (Tree)malloc(sizeof(struct Node));
    validateAlloc(n);
    n->value = value;
    n->corresponding = corresponding;
    n->left = left;
    n->right = right;
    return n;
}

Tree *insert(Tree *treePtr, char **x) {
    if (*treePtr == NULL) {
        *treePtr = createTree(x, NULL, NULL, NULL);
        return treePtr;
    }
    else if (strcmp(*(*treePtr)->value, *x) < 0) {
        return insert(&((*treePtr)->right), x); //krzaczy jak poddrzewo to NULL
    }
    else if (strcmp(*(*treePtr)->value, *x) > 0) {
        return insert(&((*treePtr)->left), x);
    }
    else {
        return treePtr;
    }
}

void removeTree(Tree t) {
    if (t != NULL) {
        removeTree(t->left);
        removeTree(t->corresponding);
        removeTree(t->right);
        free(*t->value);
        free(t);
    }
}

static void removeValueAndCorresponding(Tree *t) {
    if (*t != NULL) {
        removeTree((*t)->corresponding);
        free(*((*t)->value));
    }
}

static Tree *removeMin(Tree *treePtr) {
    if (*treePtr == NULL) {
        return NULL;
    }
    else {
        if ((*treePtr)->left == NULL) {
            Tree *prev;
            *prev = *treePtr;
            
            *treePtr = (*treePtr)->right;
            return prev;
        }
        else {
            return removeMin(&((*treePtr)->left));
        }
    }
}

void removeElement(Tree *treePtr, char *x) {
    if (*treePtr != NULL) {
        if (strcmp(*(*treePtr)->value, x) < 0) {
            removeElement(&((*treePtr)->right), x);
        }
        else if (strcmp(*(*treePtr)->value, x) > 0) {
            removeElement(&((*treePtr)->left), x);
        }
        else {
            if ((*treePtr)->right == NULL) {
                Tree *prev = treePtr;
                *treePtr = (*treePtr)->left;

                removeValueAndCorresponding(prev);
                free(prev);
            }
            else {
                Tree *removedMin;
                removedMin = removeMin(&((*treePtr)->right));

                removeValueAndCorresponding(treePtr);
                (*treePtr)->value = (*removedMin)->value;
                (*treePtr)->corresponding = (*removedMin)->corresponding;
                removeValueAndCorresponding(removedMin);
                free(*removedMin);
            }
        }
    }
}

void printTree(Tree t) {
    if (t != NULL) {
        printTree(t->left);
        printf("%s\n", *(t->value));
        printTree(t->right);
    }
}

Tree *findTree(Tree t, char *value) {
    if (t == NULL) {
        return NULL;
    }

    if (strcmp(*(t->value), value) < 0) {
        return findTree(t->right, value);
    }
    if (strcmp(*(t->value), value) > 0) {
        return findTree(t->left, value);
    }
    
    return &t;
}
