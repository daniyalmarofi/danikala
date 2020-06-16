#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function changes the price of a good in the store
void doChangeGoodsPrice(char *input, struct user *loggedinUser, struct good *goodsHead)
{
    // getting and checking goodName and goodPrice from input
    char *goodName = strtok(NULL, " ");
    if (checkInput(goodName))
    {
        free(input);
        return;
    }
    char *goodPrice = strtok(NULL, " ");
    if (checkInput(goodPrice))
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

    int goodPriceValue = atoi(goodPrice);
    if (goodPriceValue <= 0)
    {
        printf("Wrong Input! Try again!");
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
            printf("you can not change this good!");
            free(input);
            return;
        }

        searchedGood->goodPrice = goodPriceValue;

        free(input);
        printf("Goods Proce Successfully changed.");
    }
    else
    {
        free(input);
        printf("this good does not exist.");
    }
}
