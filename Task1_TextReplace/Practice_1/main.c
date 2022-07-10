#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myErrors.h"
#include "Func.h"

#define MAX_SIZE 512
#define ERR_WRONG_CMD_ARGS "ERROR: wrong number of arguments"


// Параметры:
// argv[1] - имя входного файла
// argv[2] - имя выходного файла
// argv[3] - заменяемая последовательность
// argv[4] - заменяющая последовательность
int main(int argc, char* argv[])
{
	if (argc != 5) 
	{
		fprintf_s(stderr, ERR_WRONG_CMD_ARGS);
		return -1;
	}
	FILE* FileInput, * OutputFile;     // Входной и выходной файлы
	char Buf[MAX_SIZE];  // Символьный буфер
	size_t L, L3, L4, i;
	int Sub;
	// Этап 1 - Загрузка
	FileInput = fopen(argv[1], "rb");  // Открытие файла на чтение
	L = fread(Buf, 1, MAX_SIZE, FileInput);   // Чтение в буфер
	fclose(FileInput);              // Закрытие входного файла
	// Поскольку аргументы командной строки имеют тип char*,
	// то здесь использовать strlen МОЖНО (и нужно, иначе длины последовательностей никак не узнать)
	L3 = strlen(argv[3]);     // Расчёт длин последовательностей
	L4 = strlen(argv[4]);
	// Этап 2 - Обработка
	OutputFile = fopen(argv[2], "wb");  // Создание выходного файла
	while (1)                // Цикл поиска заменяемых последовательностей
	{
		Sub = MyStrStr(Buf, L, argv[3], L3);    // Поиск подстроки
		if (Sub < 0)                   // Подстрока не найдена
		{
			fwrite(Buf, 1, L, OutputFile);         // Записать остаток буфера
			break;                     // И прекратить обработку
		}
		fwrite(Buf, 1, Sub, OutputFile);        // Запись буфера до подстроки
		fwrite(argv[4], 1, L4, OutputFile);     // Запись заменяющей последовательности
		Sub += L3;                    // Кол-во удаляемых символов
		for (i = Sub; i <= L; i++)         // Удаление первых dL символов из буфера
			Buf[i - Sub] = Buf[i];         // Путём сдвига влево
		L -= Sub;                     // Декремент длины строки в буфере
	}
	fclose(OutputFile);   // Закрытие выходного файла
	return 0;
}