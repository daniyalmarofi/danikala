#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif
#include "usersLinkedList.c"
// #include "usersLinkedList.h"

//** this function signs up a new user
void doSignup(char *input, struct user *usersHead)
{
    // getting and checking username and password and usertype from input
    char *username = strtok(NULL, " ");
    if (checkInput(username))
    {
        free(input);
        return;
    }
    char *password = strtok(NULL, " ");
    if (checkInput(password))
    {
        free(input);
        return;
    }
    char *userType = strtok(NULL, " ");
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
    struct user *searchedUser = findUser(usersHead, username, userType);
    if (searchedUser != NULL)
    {
        usernameExists = 1;
        printf("this username is taken. Please try another.");
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

        free(input);

        addUser(usersHead, newUsername, newPassword, 0, newUserType);

        printf("user signed up.");
    }
    return;
}
