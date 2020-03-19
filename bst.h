#ifndef BST_H
#define BST_H

#ifndef _STDBOOL_H
#include <stdbool.h>
#endif /* _STDBOOL_H */

#ifndef _STDIO_H
#include <stdio.h>
#endif /* _STDIO_H */

#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* _STDLIB_H */

#ifndef _STRING_H
#include <string.h>
#endif /* _STRING_H */

#ifndef ALLOC_H
#include "alloc.h"
#endif /* ALLOC_H */


struct Node;

typedef struct Node* Tree;

// Type representing a Binary Search Tree's node.
// 
// -value, left and right are standard records of a BST node.
// -corresponding is a record pointing to a BST linked to this Node
//  in a "Tree of trees" structure.
// Every Node can have a value and a corresponding BST linked to it.
struct Node {
    char *value;
    Tree left, right;
    Tree corresponding;
};


// Create a new Tree using given arguments and return it.
// 
// Function's arguments correspond to struct Node's records.
Tree createTree(char *value, Tree left, Tree right, Tree corresponding);


// Insert a value to the Tree linked to treePtr (if it's not already there)
// and return a pointer to the created Node as a result.
// If a Node with that value existed in this Tree, return a pointer to it.
// 
// Having the pointer to the created Node returned makes adding further values
// to its corresponding Tree possible.
// 
// Works as a typical insert and findTree combined.
// 
// Additionally, changes *inserted to true, if value was indeed inserted.
// Changes *inserted to false if value was present before insertion.
Tree insertAndFind(Tree *treePtr, char *value, bool *inserted);


// Free Tree t from memory, as well as all of its values and correspondings.
void removeTree(Tree t);


// Remove Node with its value equal to the value given in this function's call,
// as well as it's value and corresponding, from the Tree linked to treePtr.
// Additionally free all removed objects from memory.
// 
// Doesn't do anything if a Node with this value doesn't exist.
void removeElement(Tree *treePtr, char *value);


// Display all values present in Tree t sorted lexicographically,
// according to extended ASCII sign values, onto stdin.
// Values present in corresponding Trees are not displayed.
void printTree(Tree t);


// Return a pointer to the Node of Tree t, with its value equal to the value
// given in this function's call (if it exists).
// Return NULL if the Node hasn't been found.
Tree findTree(Tree t, char *value);


// Return a pointer to the subtree of Tree linked to treePtr,
// with its root having value equal to the value given in this function's call
// (if it exists).
// Return NULL if the subtree hasn't been found.
// 
// A more general version of findTree, operating on pointers.
Tree *findTreePtr(Tree *treePtr, char *value);


#endif /* BST_H */
