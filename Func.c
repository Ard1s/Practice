#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция определения индекса первого вхождения последовательности Sub размером L2
// в последовательность Buf размером L2
// Возвращает -1, если вхождения не нейдены

int MyStrStr(char Buf[], size_t L1, char* Sub, size_t L2)
{
	int i;

	if (!L2)
		return -1;       // Пустая подстрока - вхождений нет
	for (i = 0; i <= L1 - L2; i++)    // Перебор всех возможных подстрок
		if (!memcmp(&Buf[i], Sub, L2))
			return i;  // Сравнение байтов в памяти
	return -1;  // Подстрока не найдена
}