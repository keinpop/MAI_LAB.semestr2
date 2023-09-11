#include <stdio.h>

#define SIZE 6

void shellSort(int arr[]) {
    for (int interval = SIZE / 2; interval > 0; interval /= 2) { // Интервал, равный размеру / 2, который будет всегда уменьшаться в 2 раза
        for (int i = interval; i < SIZE; i++) { // Проход по элементам интервала
            int tmp = arr[i]; // Временный элемент, равный i месту
            int j = i; 

            while (j >= interval && arr[j - interval] > tmp) {
                arr[j] = arr[j - interval];
                j -= interval;
            }

            arr[j] = tmp;
        }
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

    shellSort(array);

    printf("Отсортированный массив:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
    return 0;
}