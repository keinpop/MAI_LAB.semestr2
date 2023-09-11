#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"

int is_empty(vec_a *va) {
    return va->size == 0;
}

void create_vec_a(vec_a* va) {
    va->allocated = 1;
    va->size = 0;
    va->begin = malloc(va->allocated * sizeof(element_a));
}

void create_vec_m(vec_m* vm) {
    vm->allocated = 1;
    vm->size = 0;
    vm->begin = malloc(vm->allocated * sizeof(int));
}

void delete_vec_a(vec_a* va) { // !!!ЗДЕСЬ ВОЗМОЖНА УТЕЧКА ПАМЯТИ!!!
    free(va->begin);
    va->allocated = 0;
    va->size = 0;
    va->begin = NULL;
}

void delete_vec_m(vec_m* vm) {
    free(vm->begin);
    vm->allocated  = 0;
    vm->size = 0;
    vm->begin = NULL;
}

void insert_value_vec_a(vec_a* va, int column, Item value, int index) {
    if (va->size + 1 >= va->allocated) {
        va->allocated *= 2;
        va->begin = realloc(va->begin, sizeof(element_a) * va->allocated);
    }
    va->begin[va->size].column = column;
    va->begin[va->size].value = value;
    va->begin[va->size].index_next = index;
    ++va->size;
}

void insert_value_vec_m(vec_m* vm, int value) {
    if (vm->size + 1 >= vm->allocated) { // Проверка на необходимость выделения еще памяти
        vm->allocated *= 2;
        vm->begin = realloc(vm->begin, sizeof(int) * vm->allocated);
    }
    vm->begin[vm->size++] = value;
}

void print_vec_a(vec_a* va) {
    if (!is_empty(&va)) {
        printf("Vector A = ");
        for (int i = 0; i < va->size; i++) {
            printf("(%d;", va->begin[i].column);
            printf("%.1f;", va->begin[i].value);
            printf("%d) ", va->begin[i].index_next);
        }
        printf("\n");
    }
}

void print_vec_m(vec_m* vm) {
    printf("Vector M = ( ");
    for (int i = 0; i < vm->size; i++) {
        printf("%d ", vm->begin[i]);
    }
    printf(")\n");
}

vec_a copy_from(vec_a* va) {
    vec_a copyVa;
    create_vec_a(&copyVa);
    for (int i = 0; i < va->size; i++) {
        insert_value_vec_a(&copyVa, va->begin[i].column, va->begin[i].value, va->begin[i].index_next);
    }
    return copyVa;
}

void product_element_column(vec_a* va) {
    int column = 0;
    for (int i = 0; i < va->size; i++) {
        if (va->begin[i].column < column) {
            column = va->begin[i].column;
        }
    }
    printf("%d - column\n", column);
    // for (int i = 0; i < column; i++) {
    //     for (int j = 0; j < va->size; j++) {
    //         if (va->begin[j].column == i) {
    //             printf("Column %d: %d\n", i, va->begin[j].value);
    //         }
    //     }
    // }
}