#include <stdio.h>
#include <stdbool.h>

#define SIZE 6

void swap(int* xp, int* yp) { // Функция смены местами двух 
    int tmp = *xp;
    *xp = *yp;
    *yp = tmp;
}

void bubbleSort(int arr[]) {
    bool swapped; // Булево значение проверки на свап

    for (int i = 0; i < SIZE - 1; i++) { // Проходимся по массиву
        swapped = false; // Не было swap

        for (int j = 0; j < SIZE - i - 1; j++) { // Проходимся по элементу для сортировки
            if (arr[j] > arr[j + 1]) { // Если один больше другого
                swap(&arr[j], &arr[j + 1]); // Меняем его с другим
                swapped = true; // swap был
            }
        }

        if (swapped == false) // Если swap не было
            break; // Пропускаем итерацию
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

    bubbleSort(array);

    printf("Отсортированный массив:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
    return 0;
}