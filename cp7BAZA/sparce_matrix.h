#ifndef __SPARCE_MATRIX__
#define __SPARCE_MATRIX__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"

typedef float Item;

typedef struct _vector_m {
    int* begin;
    int size;
    int allocated;
} vec_m;

typedef struct _element_a { // _vector_a
    int column;
    Item value;
    int index_next;
} element_a;

typedef struct _vector_a {
    element_a* begin;
    int size;
    int allocated;
} vec_a;

int is_empty(vec_a *va);
void create_vec_a(vec_a* va); // Создание вектора А
void create_vec_m(vec_m* vm); // Создание вектора M

void delete_vec_a(vec_a* va);
void delete_vec_m(vec_m* vm);

void insert_value_vec_a(vec_a* va, int column, Item value, int index);
void insert_value_vec_m(vec_m* vm, int value);

void print_vec_a(vec_a* va);
void print_vec_m(vec_m* vm);

vec_a copy_from(vec_a* va);

void product_element_column(vec_a* va);
#endif // __SPARCE_MATRIX__