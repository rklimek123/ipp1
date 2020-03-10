#ifndef BST_H
#define BST_H

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef ALLOC_H
    #include "alloc.h"
#endif

struct Node;

typedef struct Node* Tree;

struct Node {
    char **value;
    Tree corresponding; //for making "Tree of Trees" like structures
    Tree left, right;
};

Tree createTree(char **, Tree, Tree, Tree);

extern Tree *insert(Tree *, char **);

extern void removeTree(Tree);

extern void removeElement(Tree *, char *);

extern void printTree(Tree);

extern Tree *findTree(Tree, char *);

#endif /* BST_H */