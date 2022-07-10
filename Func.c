#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ������� ����������� ������� ������� ��������� ������������������ Sub �������� L2
// � ������������������ Buf �������� L2
// ���������� -1, ���� ��������� �� �������

int MyStrStr(char Buf[], size_t L1, char* Sub, size_t L2)
{
	int i;

	if (!L2)
		return -1;       // ������ ��������� - ��������� ���
	for (i = 0; i <= L1 - L2; i++)    // ������� ���� ��������� ��������
		if (!memcmp(&Buf[i], Sub, L2))
			return i;  // ��������� ������ � ������
	return -1;  // ��������� �� �������
}