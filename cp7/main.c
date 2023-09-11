#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"
#include "sparce_matrix.h"

// m - КОЛИЧЕСТВО СТРОК, n - КОЛИЧЕСТВО СТОЛБЦОВ!!!
void added_element_vector_a(vec_a* va, FILE* file) {
    int m, n;
    fscanf(file, "%d", &m); // Строка
    fscanf(file, "%d", &n); // Столбец

    for (int i = 0; i < m; i++) {
        int nonzeroCount = 0; // Счетчик ненулевых элементов в текущей строке
        int lastInsertedIndex = -1; // Индекс последнего вставленного элемента

        for (int j = 0; j < n; j++) {
            Item num;
            fscanf(file, "%f", &num);

            if (num != 0) {
                int column = j;
                Item value = num;
                int index = -1;
                insert_value_vec_a(va, column, value, index);
                nonzeroCount++;

                if (lastInsertedIndex != -1) {
                    va->begin[lastInsertedIndex].index_next = va->size - 1;
                }
                lastInsertedIndex = va->size - 1;
            }
        }

        if (nonzeroCount == 0 && lastInsertedIndex != -1) {
            va->begin[lastInsertedIndex].index_next = -1;
        }
    }
    rewind(file); // Перемещение указателя чтения в начало файла
}

void added_element_vector_m(vec_m* vm, vec_a* va, FILE* file) {
    int m, n;
    fscanf(file, "%d", &m); // Строка
    fscanf(file, "%d", &n); // Столбец
    vec_a copyVa = copy_from(va);
    for (int i = 0; i < m; i++) {
        int check = 0; // Сбросить check в ноль перед каждой строкой

        Item tmpNum = 0;
        for (int j = 0; j < n; j++) {
            Item num;
            fscanf(file, "%f", &num);
            if (num != 0 && check == 0) { // Добавить условие, чтобы сохранять только первый ненулевой элемент
                tmpNum = num;
                check = 1;
            }
        }

        if (check == 0) {
            insert_value_vec_m(vm, -1);
        } else {
            int foundIndex = -1;
            for (int k = 0; k < copyVa.size; k++) {
                if (tmpNum == copyVa.begin[k].value && copyVa.begin[k].column != -1) {
                    foundIndex = k;
                    copyVa.begin[k].column = -1;
                    break; // Добавить прерывание цикла, чтобы сохранять только первое совпадение
                }
            }
            if (foundIndex != -1) {
                insert_value_vec_m(vm, foundIndex);
            }
        }
    }
    rewind(file);
    delete_vec_a(&copyVa);
}

void print_sparce_matrix(vec_a* va, vec_m* vm, FILE* fileIn) {
    int m, n;
    fscanf(fileIn, "%d", &m); // Строка
    fscanf(fileIn, "%d", &n); // Столбец
    FILE* fileOut = fopen("out.txt", "a");

    for (int i = 0; i < m; i++) {
        bool checkIndexM = false;
        int IndexM = -1;
        if (vm->begin[i] != -1) {
            checkIndexM = true;
            IndexM = vm->begin[i];
        }
        int count = 0;
        for (int k = IndexM; k != -1; k = va->begin[k].index_next) {
            count++;
        }
        int nextIndex = IndexM;
        for (int j = 0; j < n; j++) {
            if (nextIndex != -1 && va->begin[nextIndex].column == j) {
                fprintf(fileOut, "%.1f ", va->begin[nextIndex].value);
                nextIndex = va->begin[nextIndex].index_next;
            } else {
                fprintf(fileOut, "0.0 ");
            }
        }
        fprintf(fileOut, "\n");
    }
    fclose(fileOut);
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        printf("Usage:\n\t%s  FILE_FROM\n", argv[0]);
        exit(0);
    } else { 
        FILE* file = fopen(argv[1], "r");

        FILE* tmpFile = fopen(argv[1], "r");
        int firstChar = fgetc(tmpFile);
        if (firstChar == EOF) {
            printf("Check:\n\t%s  this file is empty\n", argv[1]); 
            fclose(tmpFile);
            fclose(file);
            return 0; 
        }

        vec_a vectorA;
        vec_m vectorM;

        create_vec_a(&vectorA);
        create_vec_m(&vectorM);

        added_element_vector_a(&vectorA, file);
        added_element_vector_m(&vectorM, &vectorA, file);
        
        print_vec_a(&vectorA);
        print_vec_m(&vectorM);

        Item findElem = findMaxElementSparceMatrix(&vectorA);
        divideSparceMatrixElem(&vectorA, findElem);
        print_sparce_matrix(&vectorA,&vectorM, file);

        delete_vec_a(&vectorA);
        delete_vec_m(&vectorM);
        fclose(file);
        fclose(tmpFile);
    }

    return 0;
}