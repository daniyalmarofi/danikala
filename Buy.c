#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function buys the good for the buyer
void doBuy(char* input, struct good** goods, int numberOfGoods, struct user** users, int loggedinUserId, struct buyerCart** buyerCart, int* buyerCartCount)
{
    // getting and checking goodName and goodPrice and goodCount from input
    char* goodName = strtok(NULL, " ");
    if (checkInput(goodName))
    {
        free(input);
        return;
    }
    char* goodCount = strtok(NULL, " ");
    if (checkInput(goodCount))
    {
        free(input);
        return;
    }
    char* goodSellerUsername = strtok(NULL, " ");
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
    // if good exists I'd assign the id of that good to goodExists Variable
    int goodExists = -1;
    int i = 0;
    while (i < numberOfGoods && numberOfGoods > 0)
    {
        if (!strcmp((*goods)[i].goodName, goodName))
        {
            goodExists = i;
            break;
        }
        i++;
    }

    // if good exists do the buying
    if (goodExists > -1)
    {
        if ((*goods)[goodExists].goodCount < goodCountValue)
        {
            printf("requested count is more than good count");
            free(input);
            return;
        }
        if (((*goods)[goodExists].goodPrice) * goodCountValue > (*users)[loggedinUserId].deposit)
        {
            printf("you can not afford this good.");
            free(input);
            return;
        }
        (*goods)[goodExists].goodCount -= goodCountValue;
        (*users)[loggedinUserId].deposit -= ((*goods)[goodExists].goodPrice) * goodCountValue;
        (*users)[(*goods)[goodExists].sellerId].deposit += ((*goods)[goodExists].goodPrice) * goodCountValue;

        free(input);

        (*buyerCartCount)++;
        *buyerCart = (struct buyerCart*)realloc(*buyerCart, *buyerCartCount * sizeof(struct buyerCart));
        checkMalloc(buyerCart);

        (*buyerCart)[*buyerCartCount - 1].buyerId = loggedinUserId;
        (*buyerCart)[*buyerCartCount - 1].goodId = goodExists;
        (*buyerCart)[*buyerCartCount - 1].boughtCount = goodCountValue;

        printf("The good bought successfuly!");
    }
    else
    {
        printf("this good does not exists!");
        free(input);
    }
}
