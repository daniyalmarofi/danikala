#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#include "goodsLinkedList.h"
#endif

//** This Function removes the good which user selected
void doRemoveGoods(char *input, struct user *loggedinUser, struct good *goodsHead)
{
    // getting and checking goodName from input
    char *goodName = strtok(NULL, " ");
    if (checkInput(goodName))
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

    // search for the goodName for not existing
    int goodExists = 0;
    struct good *searchedGood = findGood(goodsHead, goodName);
    if (searchedGood != NULL)
        goodExists = 1;

    // if new Good does not exists add it to goods
    if (goodExists == 1)
    {
        if (strcmp(searchedGood->seller->username, loggedinUser->username))
        {
            printf("you can not remove this good!");
            free(input);
            return;
        }

        searchedGood->status = GOOD_DELETED;

        printf("Good Successfully removed.");
    }
    else
    {
        printf("this good does not exist.");

        free(input);
    }
}
