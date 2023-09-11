#include <stdio.h>

#define SIZE 6

void insertSort(int arr[]) {
    for (int i = 1; i < SIZE - 1; i++) { // Проход по всему массиву
        int element = arr[i]; // Первый элемент всегда считается в отсортированной части
        int j = i; // проход по отсортированной части

        while (j > 0 && arr[j - 1] > element) { // Проход по отсортированой части
            arr[j] = arr[j - 1]; // Сдвиг элемента в массиве
            j--; // Процесс движения
        }
        arr[j] = element; // Встаем на нужное место
    }
}

int main()
{
    int array[SIZE] = {6, 4, 1, 0, 9, 3};

    printf("Неотсортированный массив:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");

    insertSort(array);

    printf("Отсортированный массив:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
    return 0;
}