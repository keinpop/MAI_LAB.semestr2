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
} Vector;

void vector_create(Vector* v); // Создание вектора
void vector_delete(Vector* v);
void vector_push_back(Vector* v, int value);
void vector_printout(Vector* v);
#endif // __VECTOR_H__