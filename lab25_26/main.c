#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"
void instruction() {
    printf("\n'help' - calls the instruction to the program\n");
    printf("'pushf' - adds elemetns to front space\n");
    printf("'pushb' - adds elements to back space\n");
    printf("'popf' - delets elements to front space\n");
    printf("'popb' - delets elements to back space\n");
    printf("'deldq' - delets all elements in deque\n");
    printf("'run' - you are using bubble sort for recorded deque\n");
    printf("'print' - output in terminal your deque\n");
    printf("'quit' - you will exit the program\n\n");
}
int main()
{
    Deque *dq = malloc(sizeof(Deque)); 
    if (dq == NULL) {
        printf("Error: memory allocation failed\n");
        return 1;
    }
    initDeque(dq);

    char str[9];
    int data;
    printf("Hello, you can use this command for working to deque\n");
    instruction();
    printf("If you need instructions again, use the command: 'help'\n");
    while(1) {
        printf("Enter command -> ");
        scanf("%7s", str);
        if (!strcmp(str, "pushf")) {
            printf("Enter element to insert at front: \n");
            scanf("%d", &data);
            pushFront(dq, data);
            printf("You have added an element!\n");
            printf("\n");
        } else if (!strcmp(str, "pushb")) {
            printf("Enter element to insert at back: \n");
            scanf("%d", &data);
            pushBack(dq, data);
            printf("You have added an element!\n");
            printf("\n");
        } else if (!strcmp(str, "popf")) {
            if (isEmpty(dq)) {
                printf("Nothing to delete - deque is empty.\n");
            } else {
                printf("%d - you have delete this element\n", dq->front->value);       
                popFront(dq);
                printf("You removed the front element!\n");
            }
        } else if (!strcmp(str, "popb")) {
            if (isEmpty(dq)) {
                printf("Nothing to delete - deque is empty.\n");
            } else {
            printf("%d - you have delete this element\n", dq->back->value);
            popBack(dq);
            printf("You removed the back element!\n");
            }
        } else if (!strcmp(str, "deldq")) {
            if (isEmpty(dq)) {
                printf("Nothing to delete - deque is empty\n");
            } else {
                deleteDq(dq);
                printf("You have deleted all elements in deque.\n");
            }
        } else if (!strcmp(str, "run")) {
            if (isEmpty(dq)) {
                printf("Nothing to sort - deque is empty\n");
            }
            if (dq->size == 1) {
                printf("Deque has only one element!\n");
            } else if (dq->size > 1) {
                bubbleSort(dq);
                printf("Done!\n");
            }
        } else if (!strcmp(str, "print")) {
            if (isEmpty(dq)) {
                printf("You are not added elements deque!\n");
            } else {
                printDq(dq);
            } 
        } else if (!strcmp(str, "quit")) {
            if (dq->size == 1) {
                deleteDq(dq);
                free(dq);
                exit(1);
            } else if (dq->size == 0) {
                free(dq); 
                exit(1); 
            } else {
                deleteDq(dq);
                free(dq); 
                exit(1); 
            }
        } else if(!strcmp(str, "help")) {
            instruction();
        } else {
            printf("That command doesnt exist, try command 'help'\n");
        }
    }
    return 0;
}
