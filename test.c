#include <stdio.h>
#include <stdlib.h>

char *getInput()
{
    char *input = (char *)malloc(sizeof(char));
    char inchar;
    int i = 0;
    while ((inchar = getchar()) != '\n')
    {
        input[i] = inchar;
        i++;
        input = (char *)realloc(input, sizeof(char) * i);
    }
    input[i] = '\0';
    return input;
}

int main()
{
    char *input = getInput();
    free(input);
    return 0;
}
