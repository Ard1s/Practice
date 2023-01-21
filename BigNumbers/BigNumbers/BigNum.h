#ifndef BIGNUM_H
#define BIGNUM_H

typedef struct {
	int* num;
	int size;
	int sign;
}BigNum;


// инициализация числа
void new(BigNum*, char*);
// операции сложения вычитания
void add(BigNum*, BigNum*, BigNum*);
void sub(BigNum*, BigNum*, BigNum*);
// печать числа
void print(BigNum*);
#endif 
