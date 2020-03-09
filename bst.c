#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "alloc.h"

struct Node;

typedef struct Node* Tree;

struct Node {
    char **value;
    Tree corresponding; //for making "Tree of Trees" like structures
    Tree left, right;
};

Tree createTree(char** value, Tree corresponding, Tree left, Tree right) {
    Tree n;
    n = (Tree)malloc(sizeof(struct Node));
    //validateAlloc(n);
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

void removeValueAndCorresponding(Tree *t) {
    if (*t != NULL) {
        removeTree((*t)->corresponding);
        free(*((*t)->value));
    }
}

Tree *removeMin(Tree *treePtr) {
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

int main() {
    // char *buffer;
    // size_t bufferSize = 1;
    // buffer = (char *)malloc(bufferSize * sizeof(char));
    // int cabbage = getline(&buffer,&bufferSize, stdin);

    // char *senor = "ñ";
    // printf("%d-%d-%d\n", 'a', senor[0], senor[1]);
    // printf("%d", strcmp("a", "ñ"));

    // Tree mytree;
    // char *aab;
    // char *abba;
    // char *aaa;
    // aab = (char *)malloc(sizeof(char) * 3);
    // abba = (char *)malloc(sizeof(char) * 4);
    // aaa = (char *)malloc(sizeof(char) * 3);
    // *aab = 'a';
    // *(aab + 1) = 'a';
    // *(aab + 2) = 'b';
    // *abba = 'a';
    // *(abba + 1) = 'b';
    // *(abba + 2) = 'b';
    // *(abba + 3) = 'a';
    // *aaa = 'a';
    // *(aaa + 1) = 'a';
    // *(aaa + 2) = 'a';
    // mytree = createTree(&aab, NULL, NULL, NULL);
    // insert(&mytree, &abba);
    // insert(&mytree, &aaa);
    // removeElement(&mytree, aab);
    // printAll(mytree);
    // printf("fuk");
    // removeTree(mytree);
    // free(aab);
    // free(abba);
    // free(aaa);

    return 0;
}