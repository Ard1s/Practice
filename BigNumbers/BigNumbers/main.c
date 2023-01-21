#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include "BigNum.h"

char menu() {
	printf("\n===== menu =====\n");
	printf("1. input a\n");
	printf("2. input b\n");
	printf("3. operation +\n");
	printf("4. operation -\n");
	printf("0. exit\n");
	printf("================\n");
	return getch();
}

void input(BigNum* num) {
	char str[256];
	while (1) {
		printf("\ninput number : 0x"); scanf("%s", str);
		new(num, &str);
		if (num->size != 0) break;
		printf("error\n");
	}
}

int main()
{
	BigNum a, b, c;
	a.num = NULL;
	b.num = NULL;
	c.num = NULL;
	char ch = 0;
	while ( 1 ) {
		switch (ch = menu()) {
			case '0': {
				free(a.num);
				free(b.num);
				free(c.num);
				return EXIT_SUCCESS;
			}
			case '1': { input(&a); break;}
			case '2': { input(&b); break; }
			case '3': { 
				add(&a, &b, &c);  print(&c); break; 
			}
			case '4': { 
				sub(&a, &b, &c);  print(&c); break;
			}
		}
	}
	return EXIT_SUCCESS;
}