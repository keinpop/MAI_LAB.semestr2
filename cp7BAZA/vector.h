#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "sparce_matrix.h"

typedef struct _vector {
    int* begin;
    int size;
    int allocated;
} vector;

void vector_create(vector* v); // Создание вектора
void vector_delete(vector* v);
void vector_push_back(vector* v, int value);
void vector_printout(vector* v);
#endif // __VECTOR_H__