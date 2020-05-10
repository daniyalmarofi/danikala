#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function adds the inputed deposit to buyer
void doDeposit(char* input, struct user** users, int loggedinUserId)
{
    // get the deposit value and convert it to integer and add it to user deposit
    char* deposit = strtok(NULL, " ");
    int depositvalue = 0;
    if (checkInput(deposit))
        return;

    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    if ((depositvalue = atoi(deposit)) > 0)
    {
        (*users)[loggedinUserId].deposit += depositvalue;
        printf("%d successfuly added to your deposit.\nNow your deposit is %d.", depositvalue, (*users)[loggedinUserId].deposit);
    }
    else
        printf("Wrong input! Try again!");

    free(input);
}
