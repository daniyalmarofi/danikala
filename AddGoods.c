#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif
#include "goodsLinkedList.h"

//** this function adds a good the store
void doAddGoods(char *input, struct user *loggedinUser, struct good *goodsHead)
{
    // getting and checking goodName and goodPrice and goodCount from input
    char *sellerUsername = strtok(NULL, " ");
    if (checkInput(sellerUsername))
    {
        free(input);
        return;
    }
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
    char *goodCount = strtok(NULL, " ");
    if (checkInput(goodCount))
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
    int goodCountValue = atoi(goodCount);
    if (goodPriceValue <= 0 || goodCountValue <= 0)
    {
        printf("Wrong Input! Try again!");
        free(input);
        return;
    }

    if (strcmp(sellerUsername, loggedinUser->username))
    {
        printf("you can not add or change this good!");
        free(input);
        return;
    }

    // search for the goodName for not existing
    int goodExists = 0;
    struct good *searchedGood = findGood(goodsHead, goodName);
    if (searchedGood != NULL)
        goodExists = 1;

    // if new Good does not exists add it to goods
    if (goodExists == 0)
    {
        char *newGoodname = (char *)malloc(sizeof(char) * strlen(goodName));
        checkMalloc(newGoodname);
        strcpy(newGoodname, goodName);

        free(input);
        // add good at the end of list
        addGood(goodsHead, loggedinUser, newGoodname, goodPriceValue, goodCountValue, GOOD_ACTIVE);
        printf("Good Successfully added.");
    }
    else
    {
        if (!strcmp(searchedGood->seller->username, loggedinUser->username))
        {
            searchedGood->goodCount = goodCountValue;
            printf("goodCount changed!");
        }
        else
            printf("you are not the seller of this good!");

        free(input);
    }
}
