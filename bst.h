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

extern struct Node;
typedef struct Node* Tree;

extern Tree createTree(char **, Tree, Tree, Tree);

extern void insert(Tree *, char **);

extern void removeTree(Tree);

extern void removeElement(Tree *, char *);

extern void printTree(Tree);

extern void findTree(Tree);

#endif