#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_SIZE_ALL (1<<13)
#define MAX_SIZE_NLOGN (1<<20)
#define ARRAY_SIZE (1<<23)
#define USAGE_MESSAGE   "Usage: %s FROM TO < INPUT_FILE\n"
#define OOM_MESSAGE "%s: error: out of memory\n"

#define NUM_OF_REPETITIONS 15

int main(int argc, char* argv[])
{
    if (argc != 3) 
    {
        fprintf(stderr, USAGE_MESSAGE, argv[0]);
        return 1;
    }
}
