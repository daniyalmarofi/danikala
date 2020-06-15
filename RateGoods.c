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

    // check if the goodName exists or not
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
        if (!strcmp(current->boughtGood->goodName, goodName) && !strcmp(current->boughtGood->seller->username, goodSellerUsername) && !strcmp(current->buyer->username, loggedinUser->username) && current->rated == BUYERNOTRATED)
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

    // so you can rate the good.
    currentUserBasket->rated = BUYERRATED;
    currentUserBasket->boughtGood->numberOfRatings += 1;
    currentUserBasket->boughtGood->sumOfRates += userRateValue;

    free(input);

    printf("The good rated successfuly!");
}
