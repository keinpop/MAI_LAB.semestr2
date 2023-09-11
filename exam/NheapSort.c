#include <stdio.h>

#define SIZE 6

void swap(int* px, int* py) {
    int tmp = *px;
    *px = *py;
    *py = tmp;
}

void heapify(int arr[], int n, int i) {
    // Находим больший среди корня, левого и правого потомков
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Меняем местами и продолжаем строить, если корень не больше большего
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[]) {
    // Строим максимальную пирамиду 
    for (int i = SIZE / 2 - 1; i >= 0; i--)
        heapify(arr, SIZE, i);
    
    // Сортировка
    for (int i = SIZE - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);

        // Поднимаем больший элемент вверх
        heapify(arr, i, 0);
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

    heapSort(array);

    printf("Отсортированный массив:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
    return 0;
}