#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function checks malloc and exits program if error
void checkMalloc(void* pointer)
{
    if (pointer == NULL)
    {
        printf("Memory Allocation Error!");
        exit(EXIT_FAILURE);
    }
}

//** this function checks for user given parameters
int checkInput(void* pointer)
{
    if (pointer == NULL)
    {
        printf("Wrong Input! Try again.");
        return 1;
    }
    return 0;
}

//** this function gets user input
char* getCommandLine()
{
    char* str;
    int ch;
    size_t size = 1;
    size_t len = 0;
    str = (char*)realloc(NULL, sizeof(char) * size);
    checkMalloc(str);
    while (EOF != (ch = getchar()) && ch != '\n')
    {
        str[len++] = ch;
        if (len == size)
        {
            str = (char*)realloc(str, sizeof(char) * (size += 16));
            checkMalloc(str);
        }
    }
    str[len++] = '\0';

    return (char*)realloc(str, sizeof(char) * len);
}
