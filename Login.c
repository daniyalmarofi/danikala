#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function logs in the signed up user
void doLogin(char* input, int numberOfUsers, struct user* users, int* loggedinUserId)
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
    int i = 0;
    while (i < numberOfUsers && numberOfUsers > 0)
    {
        if (!strcmp(users[i].username, username) && !strcmp(users[i].password, password) && !strcmp(users[i].userType, userType))
        {
            *loggedinUserId = i;
            printf("%s! Welcome to your dashboard!", users[i].username);
            break;
        }
        i++;
    }

    if (*loggedinUserId == -1)
    {
        printf("the login is invalid!");
    }
    free(input);
    return;
}