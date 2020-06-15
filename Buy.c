#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function buys the good for the buyer
void doBuy(char *input, struct good *goodsHead, struct user *loggedinUser, struct buyerCart *buyerCart)
{
    // getting and checking goodName and goodPrice and goodCount from input
    char *goodName = strtok(NULL, " ");
    if (checkInput(goodName))
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
    char *goodSellerUsername = strtok(NULL, " ");
    if (checkInput(goodSellerUsername))
    {
        free(input);
        return;
    }
    int goodCountValue = atoi(goodCount);
    if (goodCountValue <= 0)
    {
        printf("Wrong Input! Try again!");
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

    // if good exists do the buying
    if (goodExists == 1)
    {
        if (searchedGood->goodCount < goodCountValue)
        {
            printf("requested count is more than good count");
            free(input);
            return;
        }
        if ((searchedGood->goodPrice) * goodCountValue > loggedinUser->deposit)
        {
            printf("you can not afford this good.");
            free(input);
            return;
        }

        // find the last node
        struct buyerCart *last = buyerCart;
        while (last->next != NULL)
            last = last->next;

        // define the last node
        struct buyerCart *newbuyerCart = (struct buyerCart *)malloc(sizeof(struct buyerCart));
        checkMalloc(newbuyerCart);
        newbuyerCart->buyer = loggedinUser;
        newbuyerCart->boughtGood = searchedGood;
        newbuyerCart->boughtCount = goodCountValue;
        newbuyerCart->boughtPrice = searchedGood->goodPrice;
        newbuyerCart->rated = BUYERNOTRATED;
        newbuyerCart->next = NULL;

        last->next = newbuyerCart;

        // move money from buyer to seller
        searchedGood->goodCount -= goodCountValue;
        loggedinUser->deposit -= (searchedGood->goodPrice) * goodCountValue;
        searchedGood->seller->deposit += (searchedGood->goodPrice) * goodCountValue;

        free(input);

        printf("The good bought successfuly!");
    }
    else
    {
        printf("this good does not exist!");
        free(input);
    }
}
