#include "tree.h"
#include "transform.h"
#include <math.h>

void swapNode(Tree** a, Tree** b) {
    Tree* tmp = *a;
    *a = *b;
    *b = tmp;
}

void transform(Tree* t) {
    if (*t == NULL) {
        return;
    }
    if ((*t)->node.type == OPERATOR && (*t)->node.data.operatorName == '*' && (*t)->left->node.type == OPERATOR && (*t)->left->node.data.operatorName == '/' && (*t)->right->node.type == OPERATOR && (*t)->right->node.data.operatorName == '/') {
        (*t)->node.data.operatorName = '/';
        (*t)->left->node.data.operatorName = '*';
        (*t)->right->node.data.operatorName = '*';
        swapNode(&((*t)->left->right), &((*t)->right->left));
    }

    else if ((*t)->node.type == OPERATOR && (*t)->node.data.operatorName == '*' && (*t)->left->node.type == OPERATOR && (*t)->left->node.data.operatorName == '*' && (*t)->left->right->node.type == OPERATOR && (*t)->left->right->node.data.operatorName == '/' && (*t)->right->node.type == OPERATOR && (*t)->right->node.data.operatorName == '/') {
        (*t)->node.data.operatorName = '/';
        (*t)->left->right->node.data.operatorName = '*';
        (*t)->right->node.data.operatorName = '*';
        swapNode(&((*t)->left->right->right), &((*t)->right->left));
    }

    else if ((*t)->node.type == OPERATOR && (*t)->node.data.operatorName == '*' && (*t)->left->node.type == OPERATOR && (*t)->left->node.data.operatorName == '*' && (*t)->left->left->node.type == OPERATOR && (*t)->left->left->node.data.operatorName == '*' && (*t)->left->left->right->node.type == OPERATOR && (*t)->left->left->right->node.data.operatorName == '/' && (*t)->right->node.type == OPERATOR && (*t)->right->node.data.operatorName == '/') {
        (*t)->left->left->right->node.data.operatorName = '*';
        (*t)->right->node.data.operatorName = '*';
        (*t)->node.data.operatorName = '/';
        swapNode(&((*t)->left->left->right->right), &((*t)->right->left));
    }

    else if ((*t)->node.type == OPERATOR && (*t)->node.data.operatorName == '*' && (*t)->left->node.type == OPERATOR && (*t)->left->node.data.operatorName == '*' && (*t)->left->left->node.type == OPERATOR && (*t)->left->left->node.data.operatorName == '*' && (*t)->left->left->left->node.type == OPERATOR && (*t)->left->left->left->node.data.operatorName == '/' && (*t)->left->right->node.type == OPERATOR && (*t)->left->right->node.data.operatorName == '/') {
        (*t)->left->left->left->node.data.operatorName = '*';
        (*t)->left->right->node.data.operatorName = '*';
        (*t)->left->node.data.operatorName = '/';
        swapNode(&((*t)->left->left->left->right), &((*t)->left->right->left));
    }
}

void treeTransform(Tree* t) {
    if ((*t) != NULL) {
        treeTransform(&((*t)->left));
        treeTransform(&((*t)->right));

        transform(t);
    }
}

