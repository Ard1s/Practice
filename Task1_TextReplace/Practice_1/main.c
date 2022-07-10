#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myErrors.h"
#include "Func.h"

#define MAX_SIZE 512
#define ERR_WRONG_CMD_ARGS "ERROR: wrong number of arguments"


// ���������:
// argv[1] - ��� �������� �����
// argv[2] - ��� ��������� �����
// argv[3] - ���������� ������������������
// argv[4] - ���������� ������������������
int main(int argc, char* argv[])
{
	if (argc != 5) 
	{
		fprintf_s(stderr, ERR_WRONG_CMD_ARGS);
		return -1;
	}
	FILE* FileInput, * OutputFile;     // ������� � �������� �����
	char Buf[MAX_SIZE];  // ���������� �����
	size_t L, L3, L4, i;
	int Sub;
	// ���� 1 - ��������
	FileInput = fopen(argv[1], "rb");  // �������� ����� �� ������
	L = fread(Buf, 1, MAX_SIZE, FileInput);   // ������ � �����
	fclose(FileInput);              // �������� �������� �����
	// ��������� ��������� ��������� ������ ����� ��� char*,
	// �� ����� ������������ strlen ����� (� �����, ����� ����� ������������������� ����� �� ������)
	L3 = strlen(argv[3]);     // ������ ���� �������������������
	L4 = strlen(argv[4]);
	// ���� 2 - ���������
	OutputFile = fopen(argv[2], "wb");  // �������� ��������� �����
	while (1)                // ���� ������ ���������� �������������������
	{
		Sub = MyStrStr(Buf, L, argv[3], L3);    // ����� ���������
		if (Sub < 0)                   // ��������� �� �������
		{
			fwrite(Buf, 1, L, OutputFile);         // �������� ������� ������
			break;                     // � ���������� ���������
		}
		fwrite(Buf, 1, Sub, OutputFile);        // ������ ������ �� ���������
		fwrite(argv[4], 1, L4, OutputFile);     // ������ ���������� ������������������
		Sub += L3;                    // ���-�� ��������� ��������
		for (i = Sub; i <= L; i++)         // �������� ������ dL �������� �� ������
			Buf[i - Sub] = Buf[i];         // ���� ������ �����
		L -= Sub;                     // ��������� ����� ������ � ������
	}
	fclose(OutputFile);   // �������� ��������� �����
	return 0;
}