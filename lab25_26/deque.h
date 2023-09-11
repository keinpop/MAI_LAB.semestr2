#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <stdio.h>
#include <stdlib.h>

typedef int Item; 

typedef struct _deque_node {
    struct _deque_node *prev; 
    struct _deque_node *next; 
    Item value; 
} Deque_node; 

typedef struct _deque { 
    Deque_node *front;  
    Deque_node *back; 
    int size; 
} Deque;


// Функции для работы с деком
void initDeque(Deque *dq);
int isEmpty(Deque *dq);
void pushFront(Deque *dq, Item data);
void pushBack(Deque *dq, Item data);
int popFront(Deque *dq);
int popBack(Deque *dq);
int deleteDq(Deque *dq);
int printDq(Deque *dq);
void bubbleSort(Deque *dq);


#endif // __DEQUE_H__