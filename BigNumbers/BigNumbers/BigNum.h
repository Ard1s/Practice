#ifndef BIGNUM_H
#define BIGNUM_H

typedef struct {
	int* num;
	int size;
	int sign;
}BigNum;


// ������������� �����
void new(BigNum*, char*);
// �������� �������� ���������
void add(BigNum*, BigNum*, BigNum*);
void sub(BigNum*, BigNum*, BigNum*);
// ������ �����
void print(BigNum*);
#endif 
