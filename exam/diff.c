#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STRING_SIZE 100

bool compareFiles(char* filename1, char* filename2) { // Функция сравнения двух файлов
    FILE* file1 = fopen(filename1, "r"); // Открываем на чтение 1 файл 
    FILE* file2 = fopen(filename2, "r"); // Открываем на чтение 2 файл

    if (file1 == NULL || file2 == NULL) { // Если файлы не открылись
        printf("Ошибка при открытии файла\n");
    } 

    int lineNumber = 1; // Счетчик строк
    char str1[STRING_SIZE], str2 [STRING_SIZE]; // Строки на чтение файла
    bool isDifferent = false; // Отличается

    while (true) { // Бесконечный цикл
        char* result1 = fgets(str1, STRING_SIZE, file1); 
        char* result2 = fgets(str2, STRING_SIZE, file2); 
        
        if (result1 == NULL && result2 == NULL) { // Достигнут конец обоих файлов
            break;
        }

        if (result1 == NULL || result2 == NULL) {
            printf("Файлы имеют разное количество строк\n");
            isDifferent = true;
            break;
        }

        if (strcmp(str1, str2) != 0) { // Если не равны
            printf("Файлы отличаются на строке %d:\n", lineNumber);
            printf("%s: %s", filename1, str1);
            printf("%s: %s", filename2, str2);
            isDifferent = true;
        }
        lineNumber++;
    } 

    fclose(file1);
    fclose(file2);

    if (!isDifferent) { // Если совпало
        printf("Файлы идентичны\n");
    }

    return !isDifferent;
}

int main(int argc, char* argv[]) 
{
    if (argc != 3) {
        printf("\tИспользование: %s FILE1 FILE2\n", argv[0]);
        return 0;
    }

    char* filename1 = argv[1];
    char* filename2 = argv[2];

    compareFiles(filename1, filename2);

    return 0;
}