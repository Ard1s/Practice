#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encoder(const char*, char*);

int main(void)
{
    char s[1000];
    char encoded[1000];

    printf("Welcome to the text encoder program - Written by James McLennan\n\n");
    printf("Please enter text to encode: ");
    fgets(s, 1000, stdin);
    encoder(s, encoded);
    printf("The encoded message = %s", encoded);
    return 0;
}

void encoder(const char* s, char* encoded)
{
    char code1[] = "CUTSDIR";
    char code2[] = "abcdefg";
    int i;
    int r = 0;
    int e = 0;

    for (i = 0; i < strlen(s); i++)
    {
        while (i < strlen(s))
        {
            if (s[i] == code1[r])
            {
                strncat(encoded, &code2[r], 1);
                break;
            }
            else if (s[i] == code2[e])
            {
                strncat(encoded, &code1[e], 1);
                break;
            }
            else if (r == 7 && e == 7)
            {
                strncat(encoded, &s[i], 1);
                break;
            }
            r++;
            e++;
        }
        r = 0;
        e = 0;
    }
}






//#include <stdio.h>
//#define MAX_SIZE_ALL (1<<13)
//#define MAX_SIZE_NLOGN (1<<20)
//#define ARRAY_SIZE (1<<23)
//
//#define NUM_OF_REPETITIONS 15
//
//int main(int argc, char* argv[])
//{
//
//}