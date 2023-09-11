#include <stdio.h>
#include <stdlib.h>

typedef int Item; // Тип данных элементов стэка

// Реализация стэка
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

void stackPrint(Stack* stack) { // Функция печати стэка
    Node* tmp = stack->last; // Временная переменная узла
    while (tmp != NULL) { // Пока последний элемент не пустой
        printf("%d\t", tmp->data); // Печать
        tmp = tmp->prev; // Двигаемся по стеку
    }
    printf("\n");
}

// Реализация очереди на стэке
typedef struct _queue {
    Stack* stack;
    size_t size;
} Queue;

void queueInit(Queue* q) {
    q->stack = (Stack*)malloc(sizeof(Stack)); // Выделяем память для стека
    stackInit(q->stack); // Инициализируем стек
    q->size = 0;
}

int queueIsEmpty(Queue* q) {
    return stackIsEmpty(q->stack) == 0;
}

size_t queueSize(Queue* q) {
    return q->size;
}

void queuePushBack(Queue* q, Item value) {
    q->size++;
    return stackPushBack(q->stack, value);
}

Item queuePopFront(Queue* q) {
    Stack tmpStack;
    stackInit(&tmpStack);

    for (int i = 0; i < queueSize(q) - 1; i++) {
        stackPushBack(&tmpStack, stackPopBack(q->stack));
    }

    Item popElem = stackPopBack(q->stack);
    q->size--;
    for (int i = 0; i < queueSize(q); i++) {
        stackPushBack(q->stack, stackPopBack(&tmpStack));
    }

    stackRemove(&tmpStack);
    return popElem;
}

void queuePrint(Queue* q) {
    if (stackIsEmpty(q->stack))
        return;
    return stackPrint(q->stack);    
}

void queueRemove(Queue* q) {
    stackRemove(q->stack);
    q->size = 0;
    free(q->stack);
}

int main()
{
    Queue q;
    queueInit(&q);
    Item a = 1, b = 2, c = 3;
    queuePushBack(&q, a);
    queuePushBack(&q, b);
    queuePushBack(&q, c);
    queuePrint(&q);
    queuePopFront(&q);
    queuePrint(&q);
    queuePushBack(&q, a);
    queuePrint(&q);
    queueRemove(&q);

    return 0;
}