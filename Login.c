#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#include "usersLinkedList.c"
#include "usersLinkedList.h"
#endif
#include "usersLinkedList.h"

//** this function logs in the signed up user
void doLogin(char *input, struct user *usersHead, struct user **loggedinUser)
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

    if (strcmp(userType, "buyer") && strcmp(userType, "seller"))
    {
        printf("Undefined User Type!");
        free(input);
        return;
    }

    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    // checking if user exists based on username and password and usertype
    int usernameExists = 0;
    struct user *searchedUser = findUser(usersHead, username);
    if (searchedUser != NULL && !strcmp(searchedUser->password, password) && !strcmp(searchedUser->userType, userType))
    {
        usernameExists = 1;
        printf("%s! Welcome to your dashboard!", searchedUser->username);
    }

    if (!usernameExists)
        printf("the login is invalid!");
    else
        *loggedinUser=searchedUser;
    free(input);
    return;
}