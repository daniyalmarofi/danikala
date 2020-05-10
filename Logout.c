#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function logs out the logged in user
void doLogout(char* input, int* loggedinUserId)
{
    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    *loggedinUserId = -1;
    printf("user Logged out!");
    free(input);
}
