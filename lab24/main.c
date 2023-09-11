#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "lexer.h"
#include "tree.h"
#include "transform.h"

int main()
{
    Token tokens[256]; // Массив переданных токенов
    size_t tokensQty = 0; // Количество токенов в массиве

    Token token; // Объявления переменной каждого токена
    printf("Please enter an expression. After finishing input, press EOF (ctrl+d)\nYour expression:");
    tokenNext(&token); // Заполнения массива токенов

    while (token.type != FINAL) { // Пока не конец массива
        tokens[tokensQty++] = token; 
        tokenNext(&token);
    }

    if (tokens[1].type == FINAL) {
        printf("\nExpression is empty\n");
        return 0;
    }

    Tree tree = treeCreate(tokens, 0, tokensQty - 1); // Создания дерева выражения

    printf("\nExpression tree:\n");
    treePrint(tree, 0);

    treeTransform(&tree); // Производим преобразования

    printf("\nSemitransformed expression tree:\n");
    treePrint(tree, 0);

    printf("\nTree's infix linearization:\n");
    treeInfix(tree);
    printf("\n");
    treeDelete(&tree);

    return 0;
}