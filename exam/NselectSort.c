#include <stdio.h>

#define SIZE 6

void selectSort(int arr[]) {
    for (int i = 0; i < SIZE - 1; i++) { // Iterate through the array
        int min = i; // Assign the current index i as the minimum index

        for (int j = i + 1; j < SIZE; j++) {
            if (arr[j] < arr[min]) 
                min = j;
        }

        if (min != i) {
            int tmp = arr[min];
            arr[min] = arr[i];
            arr[i] = tmp;
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

    selectSort(array);

    printf("Отсортированный массив:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
    return 0;
}