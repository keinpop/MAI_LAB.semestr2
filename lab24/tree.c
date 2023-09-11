#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "tree.h"

int getPriority(char c) { // Возвращение приоритета символа
    switch (c) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
    }
    return 17;
}

Tree treeCreate(Token tokens[], int indexLeft, int indexRight) { // Функция построения дерева
    Tree t = (Tree)malloc(sizeof(struct tree_node));

    if (indexLeft > indexRight) { // Если закончился проход по массиву токенов
        return NULL;
    }

    if (indexLeft == indexRight) { // Если последний токен
        t->node  = tokens[indexLeft];
        t->left  = NULL;
        t->right = NULL;
        return t;
    }

    int priority; // Переменная приоритета
    int priorityMin = getPriority('a'); // Задаем минимальный приоритет
    int brackets = 0; // Счетчик скобок
    int operPos; // Позиция оператора
    
    for (int i = indexLeft; i <= indexRight; ++i) { // Проходимся по скобкам
        if ((tokens[i].type == BRACKET) && (tokens[i].data.isLeftBracket)) { // Если это левая скобка
            ++brackets; // Прибавляем в счетчик
            continue; // Заканчиваем итерацию
        }

        if ((tokens[i].type == BRACKET) && !(tokens[i].data.isLeftBracket)) { // Если это правая скобка
            --brackets; // Отбавляем
            continue;
        }
        if (brackets > 0) { // Если уже открыты
            continue;
        }
        if (tokens[i].type == OPERATOR) { // Если это оператор
            priority = getPriority(tokens[i].data.operatorName); // Задаем приоритетом этот токен

            if (priority <= priorityMin) { // Если приоритет меньше или равен минимальному
                priorityMin = priority; // Присваиваем его
                operPos = i; // Присваиваем новую позицию
            }
        }
    }
    
    // Особый случай, новый потомок
    if ((priorityMin == getPriority('a')) && (tokens[indexLeft].type == BRACKET) && (tokens[indexLeft].data.isLeftBracket) && (tokens[indexRight].type  == BRACKET) && !(tokens[indexRight].data.isLeftBracket)) {
        free(t); // Удаляем узел
        return treeCreate(tokens, indexLeft + 1, indexRight - 1);
    }

    if (tokens[operPos].data.operatorName == '^') { // Если это степень
        brackets = 0; // Зануляем скобки

        for (int i = operPos; i >= indexLeft; --i) { // Проходимся по скобкам степени
            if ((tokens[i].type == BRACKET) && !(tokens[i].data.isLeftBracket)) { // Если правая скобка
                ++brackets;
                continue;
            }

            if ((tokens[i].type == BRACKET) && (tokens[i].data.isLeftBracket)) { // Если левая скобка
                --brackets;
                continue;
            }

            if (brackets > 0) { // Если несколько 
                continue;
            }

            if (tokens[i].type == OPERATOR) { // Если встретился оператор
                priority = getPriority(tokens[i].data.operatorName); // Меняем приоритет

                if (priority == 3) { // Если еще одна степень
                    operPos = i; // Задаем новую позицию оператора
                }
            }
        }
    }

    t->node  = tokens[operPos]; // Записываем в значение выражение
    t->left  = treeCreate(tokens, indexLeft, operPos - 1); // Запускаем рекурсию в левого потомка
    t->right = treeCreate(tokens, operPos + 1, indexRight); // Запускаем рекурсию в правого потомка

    if (t->right == NULL) {
        exit(1);
    }
    
    return t;
}

void treeDelete(Tree* t) { // Функция удаления дерева
    if ((*t) != NULL) { // Если указатель на дерево не пустой
        treeDelete(&((*t)->left)); // Рекурсивный переход к левому узлу
        treeDelete(&((*t)->right)); // Рекурсивный переход к правому узлу
    }
    free(*t); // Удаляем узел
    *t = NULL; // Указатель пуст
}

void treeInfix(Tree t) { // Вывод инфиксного выржаения
    if (t != NULL) {
        if (t->left && t->right) // Если существует и левое, и правое поддерево
            printf("("); 
        
        treeInfix(t->left); // Рекурсия перехода к левому узлу
        tokenPrint(&(t->node)); // Выводим токен
        treeInfix(t->right); // Рекурсия перехода к правому узлу

        if (t->right && t->left)
            printf(")");
    }
}

void treePrint(Tree t, size_t depth) {
    if (t != NULL) {
        for (int i = 0; i < depth; i++) {
            printf("\t"); // Вывод табуляции с уходом в глубь дерева
        }
        tokenPrint(&(t->node)); // Печатаем значения токена на этом узле дерева
        printf("\n"); // Перенос строки
        treePrint(t->left, depth + 1);
        treePrint(t->right, depth + 1);
    }
}