#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "lexer.h"

void tokenNext(Token* t) { // Считывание токенов 
    static bool canBeUnary = true;
    char c;
    
    do {
        c = fgetc(stdin);
    } while (isspace(c));
    
    if (c == EOF) { // Если конец файла
        t->type = FINAL;
    } else if (isalpha(c) || c == '_') { // Если переменная
        t->type = VARIABLE;
        t->data.variableName = c;
        canBeUnary = false;
    } else if (isdigit(c)) { // Если это число
        float result;
        ungetc(c, stdin);
        scanf("%f", &result);
        
        if (result == (int) result) { // Если целочисленное
            t->type = INTEGER;
            t->data.valueInt = (int) result;
        } else { // Если вещественное
            t->type = FLOATING;
            t->data.valueFloat = result;
        }
        canBeUnary = false;
    } else if (c == '(' || c == ')') { // Если скобка
        t->type = BRACKET;
        t->data.isLeftBracket = (c == '('); // Присваиваем скобку
        canBeUnary = t->data.isLeftBracket;
    } else if (canBeUnary && (c == '-' || c == '+')) { // Если это унарный оператор
        int sign = (c == '+') ? +1 : -1; // Если это +, унарный знак = '+', если нет - '-'
        
        do {
            c = fgetc(stdin);
        } while (isspace(c));
        
        if (isdigit(c)) { // Если это число
            ungetc(c, stdin);
            tokenNext(t);
            if (t->type == INTEGER) { // Если целочисленное
                t->data.valueInt = sign * t->data.valueInt;
            } else { // Если вещественное
                t->data.valueFloat = sign * t->data.valueFloat;
            }
        } else { // Если это оператор
            ungetc(c, stdin);
            t->type = OPERATOR;
            t->data.operatorName = '-';
            canBeUnary = true;
        }
    } else { // Если это оператор
        t->type = OPERATOR;
        t->data.operatorName = c;
        canBeUnary = true;
    }
}

void tokenPrint(Token* t) { // Печать токенов

    switch (t->type) {
        case FINAL:
            break;
        case INTEGER:
            printf("%d", t->data.valueInt);
            break;
        case FLOATING:
            printf("%lg", t->data.valueFloat);
            break;
        case VARIABLE:
            printf("%c", t->data.variableName); // %c - вывод символов
            break;
        case OPERATOR:
            printf("%c", t->data.operatorName);
            break;
        case BRACKET:
            printf("%c", (t->data.isLeftBracket) ? '(' : ')');
            break;
    }
}
