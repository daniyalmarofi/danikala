#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user
{
    char *username;
    char *password;
    char *userType;
    int deposit;
};

char *getArgument()
{
    int size = 1;
    char *str;
    int ch;
    size_t len = 0;
    str = (char *)realloc(NULL, sizeof(char));
    if (!str)
        return str;
    while (EOF != (ch = getchar()) && ch != ' ')
    {
        str[len++] = ch;
        if (len == size)
        {
            str = (char *)realloc(str, sizeof(char) * (size += 16));
            if (!str)
                return str;
        }
    }
    str[len++] = '\0';

    return (char *)realloc(str, sizeof(char) * len);
}

int main()
{
    int numberOfUsers = 0;
    struct user *users = NULL;
    char command[20];

    char *input = NULL;
    char inchar;
    int numberOfInput = 0;
    while ((inchar = getchar()) != '\n')
    {
        numberOfInput++;
        input = (char *)realloc(input, sizeof(char) * numberOfInput);
        input[numberOfInput - 1] = inchar;
    }
    input[numberOfInput] = '\0';

    char*token;

    token = strtok(input, " ");

    while (token != NULL)
    {
        printf("%s\n", token);

        token = strtok(NULL, " ");
    }

    while (1)
    {
        printf("\nEnter your Command:");
        int y = scanf("%s", command);
        if (!strcmp(command, "signup"))
        {
            printf("you are trying to signup...");
            getchar();
            char *username = getArgument();
            int usernameExists = 0;
            int i = 0;
            while (i = numberOfUsers && numberOfUsers > 0)
            {
                if (!strcmp(users[i].username, username))
                {
                    usernameExists = 1;
                    printf("this username is taken. Please try another.");
                    // clear Buffer
                    while (getchar() != '\n')
                        ;
                    free(username);
                    break;
                }
            }
            if (!usernameExists)
            {
                numberOfUsers++;
                users = (struct user *)realloc(users, numberOfUsers * sizeof(struct user));
                users[numberOfUsers - 1].username = username;
                users[numberOfUsers - 1].password = getArgument();
                users[numberOfUsers - 1].deposit = 0;
                users[numberOfUsers - 1].userType = getArgument();
                continue;
            }
        }
    }

    return 0;
}
