#ifndef HEADERS_IMPORTED
#include "commonFunctions.h"
#include "main.h"
#endif

//** this function gets a line from the file specified by FILE *fp
char *getFileLine(FILE *fp)
{
    char *str;
    int ch;
    size_t size = 1;
    size_t len = 0;
    str = (char *)realloc(NULL, sizeof(char) * size);
    checkMalloc(str);
    while (EOF != (ch = fgetc(fp)) && ch != '\n')
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

//** This Function reads the users array from defined USERSFILE .txt file
void readUsers(int *numberOfUsers, struct user **users)
{
    FILE *fp;

    fp = fopen(USERSFILE, "r");

    char *line;

    while ((line = getFileLine(fp)) && *line != NULL)
    {
        // getting and checking username and password and usertype from line
        char *username = strtok(line, ", ");
        if (checkInput(username))
        {
            free(line);
            return;
        }
        char *password = strtok(NULL, ", ");
        if (checkInput(password))
        {
            free(line);
            return;
        }
        char *userType = strtok(NULL, ", ");
        if (checkInput(userType))
        {
            free(line);
            return;
        }
        char *depositChar = strtok(NULL, ", ");
        if (checkInput(depositChar))
        {
            free(line);
            return;
        }
        int deposit = atoi(depositChar);

        if (strtok(NULL, " ") != NULL)
        {
            printf("\nError reading from users file: too much input arguments!");
            free(line);
            return;
        }

        if (strcmp(userType, "buyer") && strcmp(userType, "seller"))
        {
            printf("\nError reading from users file: Undefined User Type!");
            free(line);
            return;
        }

        // search for the username and usertype for not existing
        int usernameExists = 0;
        int i = 0;
        while (i<*numberOfUsers && *numberOfUsers> 0)
        {
            if (!strcmp((*users)[i].username, username) && !strcmp((*users)[i].userType, userType))
            {
                usernameExists = 1;
                printf("\nError reading from users file: this username is taken: %s, %s", username, userType);
                break;
            }
            i++;
        }

        // if newuser does not exists add it to user
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

            free(line);

            (*numberOfUsers)++;
            (*users) = (struct user *)realloc((*users), *numberOfUsers * sizeof(struct user));
            checkMalloc((*users));

            (*users)[*numberOfUsers - 1].username = newUsername;
            (*users)[*numberOfUsers - 1].password = newPassword;
            (*users)[*numberOfUsers - 1].deposit = deposit;
            (*users)[*numberOfUsers - 1].userType = newUserType;
        }
    }

    fclose(fp);
}