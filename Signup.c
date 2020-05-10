#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function signs up a new user
void doSignup(char* input, int* numberOfUsers, struct user** users)
{
    // getting and checking username and password and usertype from input
    char* username = strtok(NULL, " ");
    if (checkInput(username))
    {
        free(input);
        return;
    }
    char* password = strtok(NULL, " ");
    if (checkInput(password))
    {
        free(input);
        return;
    }
    char* userType = strtok(NULL, " ");
    if (checkInput(userType))
    {
        free(input);
        return;
    }

    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    if (strcmp(userType, "buyer") && strcmp(userType, "seller"))
    {
        printf("Undefined User Type!");
        free(input);
        return;
    }

    // search for the username and usertype for not existing
    int usernameExists = 0;
    int i = 0;
    while (i < *numberOfUsers && *numberOfUsers> 0)
    {
        if (!strcmp((*users)[i].username, username) && !strcmp((*users)[i].userType, userType))
        {
            usernameExists = 1;
            printf("this username is taken. Please try another.");
            break;
        }
        i++;
    }

    // if newuser does not exists add it to user
    if (!usernameExists)
    {
        char* newUsername = (char*)malloc(sizeof(char) * strlen(username));
        checkMalloc(newUsername);
        strcpy(newUsername, username);

        char* newPassword = (char*)malloc(sizeof(char) * strlen(password));
        checkMalloc(newPassword);
        strcpy(newPassword, password);

        char* newUserType = (char*)malloc(sizeof(char) * strlen(userType));
        checkMalloc(newUserType);
        strcpy(newUserType, userType);

        free(input);

        (*numberOfUsers)++;
        (*users) = (struct user*)realloc((*users), *numberOfUsers * sizeof(struct user));
        checkMalloc((*users));

        (*users)[*numberOfUsers - 1].username = newUsername;
        (*users)[*numberOfUsers - 1].password = newPassword;
        (*users)[*numberOfUsers - 1].deposit = 0;
        (*users)[*numberOfUsers - 1].userType = newUserType;
        printf("user signed up.");
    }
    return;
}
