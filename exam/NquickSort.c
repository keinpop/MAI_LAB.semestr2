#include <stdio.h>

#define SIZE 6

void swap(int* xp, int* yp) { // Функция смены местами двух 
    int tmp = *xp;
    *xp = *yp;
    *yp = tmp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Выбранный элемент разделения
    int i = (low - 1); // Крайний праый 
    
    for (int j = low; j < high; j++) { // сравниваем элементы с pivot
        if (arr[j] <= pivot) { // Если найден элемент меньше pivot'а
            i++; 
            swap(&arr[i], &arr[j]); // Поменять местами
        }
    }

    // Поменять местами pivot с большим элементом i 
    swap(&arr[i + 1], &arr[high]);

    return (i + 1); // Возвращаем точку разделения
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // находим опорный элемент такой, что
        // элементы меньше, чем точка поворота, находятся слева от точки поворота
        // элементы больше, чем точка поворота, находятся справа от точки поворота
        int pi = partition(arr, low, high);

        // Рекурсивный вызов слева от стены
        quickSort(arr, low, pi - 1);

        // Рекурсивный вызов слева от стены
        quickSort(arr, pi + 1, high);
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

    quickSort(array, 0, SIZE - 1);

    printf("Отсортированный массив:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
    return 0;
}