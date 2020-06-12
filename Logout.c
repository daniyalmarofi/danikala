#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function logs out the logged in user
void doLogout(char* input, struct user **loggedinUser)
{
    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    *loggedinUser = NULL;
    printf("user Logged out!");
    free(input);
}
