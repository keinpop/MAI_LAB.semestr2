#include <stdio.h>
#include <stdlib.h>

#include "deque.h"

void initDeque(Deque *dq) {
    dq->front = NULL;
    dq->back = NULL;
    dq->size = 0;
}

int isEmpty(Deque *dq) {
    return dq->size == 0;
}

void pushFront(Deque *dq, Item data) {
    Deque_node *dq_el = malloc(sizeof(Deque_node));
    dq_el->next = NULL;
    dq_el->prev = NULL;
    dq_el->value = data;

    if (dq->size == 0) {
        dq->front = dq_el;
        dq->back = dq_el;
    } else {    
        dq_el->prev = dq->front;
        dq->front = dq_el;
        dq_el->prev->next = dq_el;
    }
    
    dq->size++;
}

void pushBack(Deque *dq, Item data) {
    Deque_node *dq_el = malloc(sizeof(Deque_node));
    dq_el->next = NULL;
    dq_el->prev = NULL;
    dq_el->value = data;

    if (dq->size == 0) {
        dq->front = dq_el;
        dq->back = dq_el;
    } else {
        dq_el->next = dq->back;
        dq->back = dq_el;
        dq_el->next->prev = dq_el; 
    }
    dq->size++;
}

int popFront(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Nothing to delete - deque is empty.\n");
        return -1;
    }
    Deque_node *tmp = dq->front;
    if (dq->size == 1) {
        dq->front = NULL;
        dq->back = NULL;
    } else {
        Deque_node *prev_el = tmp->prev;
        prev_el->next = NULL;
        dq->front = prev_el;
    }
    free(tmp);
    dq->size--;
    return 0;
}

int popBack(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Nothing to delete - deque is empty.\n");
        return -1;
    }
    Deque_node *tmp = dq->back;
    if (dq->size == 1) {
        dq->front = NULL;
        dq->back = NULL;
    } else {
        Deque_node *next_el = tmp->next;
        next_el->prev = NULL;
        dq->back = next_el;
    }
    free(tmp);
    dq->size--;
    return 0;
}

int printDq(Deque *dq) {
    if (isEmpty(dq)) {
        return -1;
    }
    int i = 0;
    Deque_node *tmp = dq->back;
    for (i = dq->size; i != 0; i--) {
        printf("%d\t", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
    return 1;
}

int deleteDq(Deque *dq) {
    if (isEmpty(dq)) {
        return -1;
    }
    int i = 0;
    Deque_node *tmp = dq->back;
    for (i = dq->size; i != 0; i--) {
        Deque_node *next = tmp->next;
        free(tmp);
        tmp = next;
    }
    dq->back = NULL;
    dq->front = NULL;
    dq->size = 0;
}

void bubbleSort(Deque *dq) {
    if (isEmpty(dq)) {
        return;
    }
    if (dq->size == 1) {
        return;
    }
    Deque_node *current, *next;
    int i, j = 0;
    for (i = 0; i < dq->size; i++) {
        current = dq->back;
        next = current->next; 
        for (j = 0; j < dq-> size - i - 1; j++) {
            if (current->value > next->value) { // switch
                next->prev = current->prev;
                if (current->prev != NULL) {
                    current->prev->next = next;
                }
                current->next = next->next;
                if (next->next != NULL) {
                    next->next->prev = current;
                } 
                current->prev = next;
                next->next = current;
                if (j == 0) {
                    dq->back = next;
                } else if (j == dq->size  - 2) {
                    dq->front = current;
                }
                next = current->next;
            } else {
                current = next;
                next = next->next;
            }
        }
    }
}