#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "func.h"


#define ERR_WRONG_CMD_ARGS "ERROR: wrong number of arguments"
#define SUCCESFULL "-------------Succesfull! Check your output file--------------------"
#define MAX_MEMORY 1024

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
    
    FILE* InputFile, * OutputFile;
    char Buf[MAX_MEMORY];
    size_t OrigLen, RepLen;


    OrigLen = strlen(argv[3]);     
    RepLen = strlen(argv[4]);

    InputFile = fopen(argv[1], "rb");
    OutputFile = fopen(argv[2], "wb");
    
    Loop(InputFile, Buf, OutputFile, argv, OrigLen, RepLen);
    
    fclose(InputFile);
    fclose(OutputFile);
    fprintf_s(stderr, SUCCESFULL);
    fprintf_s(stderr, "\n");
    return 0;
}
