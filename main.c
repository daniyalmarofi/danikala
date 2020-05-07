#define _CRT_SECURE_NO_DEPRECATE
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

void checkMalloc(void *pointer)
{
    if (pointer == NULL)
    {
        printf("Memory Allocation Error!");
        exit(EXIT_FAILURE);
    }
}

char *getCommandLine()
{
    char *str;
    int ch;
    size_t size = 1;
    size_t len = 0;
    str = (char *)realloc(NULL, sizeof(char) * size);
    checkMalloc(str);
    while (EOF != (ch = getchar()) && ch != '\n')
    {
        str[len++] = ch;
        if (len == size)
        {
            str = (char *)realloc(str, sizeof(char) * (size += 16));
            checkMalloc(str);
        }
    }
    str[len++] = '\0';

    return (char *)realloc(str, sizeof(char) * len);
}

int main()
{

    printf("Welcome To DaniKala!");
    int numberOfUsers = 0;
    struct user *users = NULL;
    char *command;

    // token = strtok(NULL, " ");

    while (1)
    {
        printf("\nEnter your Command:");
        char *input = getCommandLine();
        checkMalloc(input);

        command = strtok(input, " ");
        if (!strcmp(command, "signup"))
        {
            char *username = strtok(NULL, " ");
            if (username == NULL)
            {
                printf("Wrong Input! Try again.");
                continue;
            }
            char *password = strtok(NULL, " ");
            if (password == NULL)
            {
                printf("Wrong Input! Try again.");
                continue;
            }

            char *userType = strtok(NULL, " ");
            if (userType == NULL)
            {
                printf("Wrong Input! Try again.");
                continue;
            }

            if (strcmp(userType, "buyer") && strcmp(userType, "seller"))
            {
                printf("Undefined User Type!");
                continue;
            }

            int usernameExists = 0;
            int i = 0;
            while (i < numberOfUsers && numberOfUsers > 0)
            {
                if (!strcmp(users[i].username, username) && !strcmp(users[i].userType, userType))
                {
                    usernameExists = 1;
                    printf("this username is taken. Please try another.");
                    free(input);
                    break;
                }
                i++;
            }

            if (!usernameExists)
            {
                char *newUsername = (char *)malloc(sizeof(char) * strlen(username));
                checkMalloc(newUsername);

                strcpy(newUsername, username);
                char *newPassword = (char *)malloc(sizeof(char) * strlen(password));
                checkMalloc(newPassword);

                strcpy(newPassword, password);
                char *newUserType = (char *)malloc(sizeof(char) * strlen(userType));
                checkMalloc(newUserType);

                strcpy(newUserType, userType);

                free(input);

                numberOfUsers++;
                users = (struct user *)realloc(users, numberOfUsers * sizeof(struct user));
                checkMalloc(users);

                users[numberOfUsers - 1].username = newUsername;
                users[numberOfUsers - 1].password = newPassword;
                users[numberOfUsers - 1].deposit = 0;
                users[numberOfUsers - 1].userType = newUserType;
                printf("user signed up.");
                continue;
            }
            else
            {
                continue;
            }
        }
        else if (!strcmp(command, "exit"))
        {
            break;
        }
        else
        {
            printf("Command Not Found!");
        }
    }

    // TODO add a for loop to clear all allocated momries
    free(users);
    return 0;
}
