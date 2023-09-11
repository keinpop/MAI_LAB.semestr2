#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum {
    FINAL,
    INTEGER,
    FLOATING,
    OPERATOR,
    VARIABLE,
    BRACKET
} TokenType;

typedef struct {
    TokenType type;
    union {
        int   valueInt;
        float valueFloat;
        char  operatorName;
        bool  isLeftBracket;
        char  variableName;
    } data;
} Token;

void tokenPrint(Token* t);
void tokenNext(Token* t);

#endif