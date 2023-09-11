#include <stdio.h>
#include <stdlib.h>

//Подключим стэк, но тк мне супер лень пилить еще и мейк 
//К таким задачкам, то я тупо запушу сюда все написанные,
//Мною фунцкии реализации работы со стеком, считаем, что:
// #include "stack.h"

typedef struct _node { // Создаем структуру узла стэка
    int data; // Поле значения
    struct _node* prev; // Указатель на следующий узел
} Node;

typedef struct _stack {
    Node* last; // Указатель на верхушку стэка
    size_t size;
} Stack;

void stackInit(Stack* stack) { // Функция инициализации стека
    stack->last = NULL; // ЗаNULLяем указатель стэка
    stack->size = 0;
}

int stackIsEmpty(Stack* stack) {
    return stack->size == 0;
}

size_t stackSize(Stack* stack) {
    return stack->size;
}

int stackTop(Stack* stack) {
    return stack->last->data;
}

void stackPushBack(Stack* stack, int value) { // Функция добавления узла в стек
    Node* newNode = (Node*)malloc(sizeof(Node)); // Аллоцируем память на новый элемент
    newNode->data = value; // Присваиваем значение новому узлу
    newNode->prev = stack->last; // Указатель нового узла на следующий является указателем дека на верхушку
    stack->last = newNode; // Указатель на верхушку стека - новый элемент
    stack->size++;
}

int stackPopBack(Stack* stack) { // Функция вытаскивания из стэка верхнего узла
    if (stack->last == NULL) { // Если стэк пуст
        return __INT_MAX__; // Выход из функции
    } else {
        int value = stack->last->data; // В переменную значения копируем значение верхушки стэка
        Node* tmp = stack->last; // Временная переменная узла стэка - указатель на верхушку
        stack->last = stack->last->prev; // Указатель на верхушку стэка на следующий после него узел
        stack->size--;
        free(tmp); // Удаляем элемент из стэка
        return value; // Возвращаем вытащенный элемент стэка
    }
}

void stackPrint(Stack* stack) { // Функция печати стэка
    Node* tmp = stack->last; // Временная переменная узла
    while (tmp != NULL) { // Пока последний элемент не пустой
        printf("%d\t", tmp->data); // Печать
        tmp = tmp->prev; // Двигаемся по стеку
    }
    printf("\n");
}

void stackRemove(Stack* stack) { // Функция удаления стэка
    if (stackIsEmpty(stack)) {
        return;
    }

    Node* tmp = stack->last;
    for (int i = 0; i < stack->size; i++) {
        Node* prevElem = tmp->prev;
        free(tmp);
        tmp = prevElem;
    }
    stack->size = 0;
    stack->last = NULL;
}

Stack stackCopyFrom(Stack* inS) { // Функция копирования элементов стэка
    Stack outS;
    stackInit(&outS);

    Stack conteiner;
    stackInit(&conteiner);

    Node* tmp = inS->last;
    for (int i = 0; i < stackSize(inS); i++) {
        stackPushBack(&conteiner, tmp->data);
        tmp = tmp->prev;
    }
    
    tmp = conteiner.last;
    for (int i = 0; i < stackSize(&conteiner); i++) {
        stackPushBack(&outS, tmp->data);
        tmp = tmp->prev;
    }

    stackRemove(&conteiner);
    return outS;
}

//##########################
//Теперь приступим к реализации задачки
//Вычисление константного булевого выражения в обратной польской записи 
//Так как я тут разговорился, напишу сложность - O(n) (n - количество входных символов)

int main() 
{
    char c, a, b;
    Stack stack;

    stackInit(&stack);

    while ((c = getchar()) != EOF) {
        if (c == '0' || c == '1') {
            stackPushBack(&stack, c - '0');
        } else if (c == '&') {
            if (stackSize(&stack) < 2) {
                printf("\nError enter, not a enought elements\n");
                exit(1);
            }
            a = stackPopBack(&stack);
            b = stackPopBack(&stack);
            stackPushBack(&stack, a & b);
        } else if (c == '|') {
            if (stackSize(&stack) < 2) {
                printf("\nError enter, not a enought elements\n");
                exit(1);
            }
            a = stackPopBack(&stack);
            b = stackPopBack(&stack);
            stackPushBack(&stack, a | b);
        } else {
            printf("\nError enter, unknown symbols\n");
            exit(1);
        }
    }
    
    if (stackSize(&stack) == 1) {
        printf("\n%d\n", stackTop(&stack));
    } else {
        printf("Not finished expression\n");
    }
    stackRemove(&stack);
    return 0;
}
// in: (1 & 1) | (1 & 0) -> 1
// out: 1 1 & 1 0 & |
// stack: 