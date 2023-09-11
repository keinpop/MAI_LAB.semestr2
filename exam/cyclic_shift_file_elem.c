#include <stdio.h>
#include <string.h>

#define STRING_SIZE 100

int fileShift(const char* filename, int shift) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return -1;
    }

    fseek(file, 0, SEEK_END); // Перемещаем указатель в конец файла
    long fileSize = ftell(file); // Получаем размер файла
    rewind(file); // Возвращаем указатель в начало файла

    char str[STRING_SIZE];
    fread(str, sizeof(char), fileSize, file); // Читаем содержимое файла в массив

    int length = strlen(str);
    shift = shift % length; // Определяем фактическое значение сдвига

    if (shift > 0) {
        char temp[shift];
        strncpy(temp, &str[length - shift], shift); // Сохраняем последние shift символов во временный массив
        memmove(&str[shift], str, length - shift); // Сдвигаем остальные символы вправо
        memcpy(str, temp, shift); // Копируем временный массив в начало строки
    } else if (shift < 0) {
        shift = -shift; // Изменяем знак сдвига
        char temp[shift];
        strncpy(temp, str, shift); // Сохраняем первые shift символов во временный массив
        memmove(str, &str[shift], length - shift); // Сдвигаем остальные символы влево
        memcpy(&str[length - shift], temp, shift); // Копируем временный массив в конец строки
    }

    fclose(file);

    FILE* outFile = fopen(filename, "w"); // Открываем файл для записи
    if (outFile == NULL) {
        printf("Ошибка при открытии файла\n");
        return -1;
    }

    fwrite(str, sizeof(char), length, outFile); // Записываем измененную строку обратно в файл

    fclose(outFile);
    return 0;
}

int main()
{
    printf("Введите имя файла:\n");
    char filename[100];
    scanf("%s", filename);  
    printf("Введите число сдвига:\n");
    int shift;
    scanf("%d", &shift);

    fileShift(filename, shift);

    return 0;
}