#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"
#include "sparce_matrix.h"

void added_element_vector_a(vec_a* va, FILE* file) {
    int m, n;
    fscanf(file, "%d", &m); // Строка
    fscanf(file, "%d", &n); // Столбец

    for (int i = 0; i < m; i++) {
        int nonzero_count = 0; // Счетчик ненулевых элементов в текущей строке
        int last_insert_index = -1; // Индекс последнего вставленного элемента

        for (int j = 0; j < n; j++) {
            Item num;
            fscanf(file, "%f", &num);

            if (num != 0) {
                int column = j;
                Item value = num;
                int index = -1;
                insert_value_vec_a(va, column, value, index);
                nonzero_count++;

                if (last_insert_index != -1) {
                    va->begin[last_insert_index].index_next = va->size - 1;
                }
                last_insert_index = va->size - 1;
            }
        }

        if (nonzero_count == 0 && last_insert_index != -1) {
            va->begin[last_insert_index].index_next = -1;
        }
    }
    rewind(file); // Перемещение указателя чтения в начало файла
}

void added_element_vector_m(vec_m* vm, vec_a* va, FILE* file) {
    int m, n;
    fscanf(file, "%d", &m); // Строка
    fscanf(file, "%d", &n); // Столбец
    vec_a copy_va = copy_from(va);
    for (int i = 0; i < m; i++) {
        int check = 0; // Сбросить check в ноль перед каждой строкой

        Item tmp_num = 0;
        for (int j = 0; j < n; j++) {
            Item num;
            fscanf(file, "%f", &num);
            if (num != 0 && check == 0) { // Добавить условие, чтобы сохранять только первый ненулевой элемент
                tmp_num = num;
                check = 1;
            }
        }

        if (check == 0) {
            insert_value_vec_m(vm, -1);
        } else {
            int found_index = -1;
            for (int k = 0; k < copy_va.size; k++) {
                if (tmp_num == copy_va.begin[k].value && copy_va.begin[k].column != -1) {
                    found_index = k;
                    copy_va.begin[k].column = -1;
                    break; // Добавить прерывание цикла, чтобы сохранять только первое совпадение
                }
            }
            if (found_index != -1) {
                insert_value_vec_m(vm, found_index);
            }
        }
    }
    rewind(file);
    delete_vec_a(&copy_va);
}

void print_sparce_matrix(vec_a* va, vec_m* vm, FILE* file_in) {
    int m, n;
    fscanf(file_in, "%d", &m); // Строка
    fscanf(file_in, "%d", &n); // Столбец
    FILE* file_out = fopen("out.txt", "a");

    for (int i = 0; i < m; i++) {
        bool check_index_m = false;
        int index_m = -1;
        if (vm->begin[i] != -1) {
            check_index_m = true;
            index_m = vm->begin[i];
        }
        int count = 0;
        for (int k = index_m; k != -1; k = va->begin[k].index_next) {
            count++;
        }
        int next_index = index_m;
        for (int j = 0; j < n; j++) {
            if (next_index != -1 && va->begin[next_index].column == j) {
                fprintf(file_out, "%.1f ", va->begin[next_index].value);
                next_index = va->begin[next_index].index_next;
            } else {
                fprintf(file_out, "0.0 ");
            }
        }
        fprintf(file_out, "\n");
    }
    fclose(file_out);
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        printf("Usage:\n\t%s  FILE_FROM\n", argv[0]);
        exit(0);
    } else { 
        FILE* file = fopen(argv[1], "r");

        FILE* tmp_file = fopen(argv[1], "r");
        int first_char = fgetc(tmp_file);
        if (first_char == EOF) {
            printf("Check:\n\t%s  this file is empty\n", argv[1]); 
            fclose(tmp_file);
            fclose(file);
            return 0; 
        }

        vec_a vector_a;
        vec_m vector_m;

        create_vec_a(&vector_a);
        create_vec_m(&vector_m);

        added_element_vector_a(&vector_a, file);
        added_element_vector_m(&vector_m, &vector_a, file);
        
        print_vec_a(&vector_a);
        print_vec_m(&vector_m);

        // product_element_column(&vector_a);

        print_sparce_matrix(&vector_a,&vector_m, file);

        delete_vec_a(&vector_a);
        delete_vec_m(&vector_m);
        fclose(file);
        fclose(tmp_file);
    }

    return 0;
}