#include <stdio.h>
#include <stdlib.h>

typedef int Item; // Тип данных элементов стэка

typedef struct _node { // Создаем структуру узла стэка
    Item data; // Поле значения
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

Item stackTop(Stack* stack) {
    return stack->last->data;
}

void stackPushBack(Stack* stack, Item value) { // Функция добавления узла в стек
    Node* newNode = (Node*)malloc(sizeof(Node)); // Аллоцируем память на новый элемент
    newNode->data = value; // Присваиваем значение новому узлу
    newNode->prev = stack->last; // Указатель нового узла на следующий является указателем дека на верхушку
    stack->last = newNode; // Указатель на верхушку стека - новый элемент
    stack->size++;
}

Item stackPopBack(Stack* stack) { // Функция вытаскивания из стэка верхнего узла
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

void stackRemove(Stack* stack) {
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

void stackInsertSort(Stack* stack) { // Функция сортировки вставкой
    Stack tmpStack; // Создаем временный стэк
    stackInit(&tmpStack); // Инициализируем в памяти его

    while (!stackIsEmpty(stack)) { // Пока стэк не пуст
        Item tmp = stackPopBack(stack); // Переменная, хронящая в себе вытащенный элемент 
        while (!(stackIsEmpty(&tmpStack)) && stackTop(&tmpStack) > tmp) { // Пока ВС не пуст и верхушка его больше вытащенного элемента
            stackPushBack(stack, stackPopBack(&tmpStack)); // Вставляем в стэк элементы временного
        }
        stackPushBack(&tmpStack, tmp); // Засовываем в ВС элементы из нашего стэка
    }

    while (!stackIsEmpty(&tmpStack)) {
        stackPushBack(stack, stackPopBack(&tmpStack)); // Переносим из временного в наш
    }
}

int main()
{
    Stack stack;
    stackInit(&stack);

    Item a = 5, b = 3, c = 1, d = 9, e = 6;
    stackPushBack(&stack, c);
    stackPushBack(&stack, a);
    stackPushBack(&stack, b);
    stackPushBack(&stack, d);
    stackPushBack(&stack, e);
    printf("\tИзначальный стэк:\n");
    stackPrint(&stack);

    stackInsertSort(&stack);
    printf("\tСтэк после сортировки:\n");
    stackPrint(&stack);
    stackRemove(&stack);

    return 0;
}