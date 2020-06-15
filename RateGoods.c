#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function rates the bought good for the buyer
void doRateGoods(char *input, struct good *goodsHead, struct user *loggedinUser, struct buyerCart *buyerCart)
{
    // getting and checking goodName and seller username and rate from input
    char *goodName = strtok(NULL, " ");
    if (checkInput(goodName))
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

    char *userRate = strtok(NULL, " ");
    if (checkInput(userRate))
    {
        free(input);
        return;
    }
    int userRateValue = atoi(userRate);
    if (userRateValue > 5 || userRateValue < 1)
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
    if (searchedGood == NULL)
    {
        printf("this good does not exist!");
        free(input);
        return;
    }

    if (strcmp(searchedGood->seller->username, goodSellerUsername))
    {
        printf("the seller username is wrong!");
        free(input);
        return;
    }

    // search history to find the bought record
    struct buyerCart *currentUserBasket = NULL;
    struct buyerCart *current = buyerCart->next;
    while (current != NULL)
    {
        if (!strcmp(current->boughtGood->goodName, goodName) && !strcmp(current->boughtGood->seller->username, goodSellerUsername) && !strcmp(current->buyer->username, loggedinUser) && current->rated == BUYERNOTRATED)
        {
            currentUserBasket = current;
            break;
        }
        current = current->next;
    }

    if (currentUserBasket == NULL)
    {
        printf("you can not rate the good with these information.");
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
