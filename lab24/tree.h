#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include "lexer.h"

typedef struct tree_node *Tree;
struct tree_node {
    Token node;
    Tree left;
    Tree right;
};

Tree treeCreate(Token tokens[], int idx_left, int idx_right);
void treeDelete(Tree* t);
void treeInfix(Tree t);
void treePrint(Tree t, size_t depth);

#endif