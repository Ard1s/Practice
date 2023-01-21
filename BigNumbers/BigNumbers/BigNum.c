#include "BigNum.h"
#include <stdio.h>

// �������� � ������������� �����
void new(BigNum* num, char* str) {	
	int i, j, length = 0;
	char ch;
	num->size = 0;
	// �������� ������
	for (i = 0; i < strlen(str); i++) {
		ch = str[i];
		// �������� ������� hex
		if ((ch >= '0' && ch <= '9') ||
			(ch >= 'a' && ch <= 'f') ||
			(ch >= 'A' && ch <= 'F')) {
			length++; continue;
		}
		return;
	}

	if (length == 0) return;

	num->size = length / 8 + (length % 8 ? 1 : 0);
	// ���������� ����� ����� � Int;
	if (num->num == NULL)
		num->num = (int*)malloc(num->size * sizeof(int));
	else
		num->num = (int*)realloc(num->num, num->size * sizeof(int));

	// ����� � 0
	for (i = 0; i < num->size; i++) num->num[i] = 0;

	int size = strlen(str);
	// ��������� �����
	for (j = 0, i = size - 1; i >= size - length; i--, j++) {
		ch = str[i];
		if (ch >= '0' && ch <= '9') ch -= '0';
		if (ch >= 'a' && ch <= 'f') ch -= 'a' - 10;
		if (ch >= 'A' && ch <= 'F') ch -= 'A' - 10;
		num->num[j / 8] |= ((unsigned int)ch) << (j % 8 * 4);
	}
	// ����������� ����� �����

	if((num->num[num->size - 1] & 0x80000000) == 0) num->sign = 0;
	else num->sign = -1;
}

// ����� �����
void print(BigNum* num) {
	if (num->num == NULL) return;
	int i;
	printf("0x");
	for (i = num->size - 1; i >= 0; i--) 
		printf("%08X", num->num[i]);
	printf("\n");
}


unsigned int ta, tb, cf;
// �������� �����
void add(BigNum* a, BigNum* b, BigNum* c) {
	if (a->num == NULL || b->num == NULL) {
		printf("error - input numbers\n");
		c->num = NULL; return;
	}
	else printf("\na + b = ");

	int i, size = a->size >= b->size ? a->size + 1: b->size + 1;
	if( c->num == NULL)
		c->num = (int*)malloc(size * sizeof(int));
	else
		c->num = (int*)realloc(c->num, size * sizeof(int));
	c->size = size;

	cf = 0;
	for (i = 0; i < c->size; i++) {
		ta = i < a->size ? a->num[i] : 0;
		tb = i < b->size ? b->num[i] : 0;
		c->num[i] = ta + tb + cf;
		// �������� ������������
		cf = ta > ta + tb ? 1 : ta + tb > c->num[i] ? 1 : 0;
	}

	// �������������� ����� �����
	if ((c->num[c->size - 1] ==  0) ||
	   ((c->num[c->size - 1] == -1) &&
		(c->num[c->size - 2] == -1))) --c->size;
	return c;
}

// ��������� �����
void sub(BigNum* a, BigNum* b, BigNum* c) {
	if (a->num == NULL || b->num == NULL) {
		printf("error - input numbers\n");
		c->num = NULL; return;
	}
	else printf("\na - b = ");

	int i, size = a->size >= b->size ? a->size + 1 : b->size + 1;
	if (c->num == NULL)
		c->num = (int*)malloc(size * sizeof(int));
	else
		c->num = (int*)realloc(c->num, size * sizeof(int));
	c->size = size;

	cf = 0;
	for (i = 0; i < c->size; i++) {
		
		ta = i < a->size ? a->num[i] : 0;
		tb = i < b->size ? b->num[i] : 0;
		c->num[i] = ta - tb - cf;
		// �������� ������������
		cf = ta < ta - tb ? 1 : ta - tb < c->num[i] ? 1 : 0;
	}

	// �������������� ����� �����
	if ((c->num[c->size - 1] == 0) ||
	   ((c->num[c->size - 1] ==-1) &&
		(c->num[c->size - 2] ==-1))) --c->size;
	return c;
}

