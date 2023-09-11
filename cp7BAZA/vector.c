#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"
#include "sparce_matrix.h"

void vector_create(vector* v) {
    v->allocated = 1;
    v->size = 0;
    v->begin = malloc(v->allocated * sizeof(int));
}

void vector_delete(vector *v) {
    free(v->begin);
    v->allocated = 0;
    v->size = 0;
    v->begin = NULL;
}

void vector_push_back(vector* v, int value) {
    if (v->size + 1 >= v->allocated) { // Проверка на необходимость выделения еще памяти
        v->allocated *= 2;
        v->begin = realloc(v->begin, sizeof(int) * v->allocated);
    }
    v->begin[v->size++] = value;
}

void vector_printout(vector* v) {
    for (int i = 0; i < v->size; i++) {
        printf("%d ", v->begin[i]);
    }
    printf("\n");
}