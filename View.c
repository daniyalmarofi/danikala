#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function shows the information of the user and history of goods
void doView(char *input, struct user *loggedinUser, struct buyerCart *buyerCart, struct good *goodsHead)
{

    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    printf("Displaying user Information:\n");
    printf("username: %s\t", loggedinUser->username);
    printf("userType: %s\t", loggedinUser->userType);
    printf("Deposit: %d\n", loggedinUser->deposit);

    if (!strcmp(loggedinUser->userType, "buyer"))
    {
        int thisUserBasket = 0;
        struct buyerCart *current = buyerCart->next;
        while (current != NULL)
        {
            if (!strcmp(current->buyer->username, loggedinUser->username))
            {
                thisUserBasket++;
                printf("----\n");
                printf("Good Name:\t\t%s\n", current->boughtGood->goodName);
                printf("Bought Price:\t\t%d\n", current->boughtPrice);
                printf("Bought Count:\t\t%d\n", current->boughtCount);
                printf("Good Rate:\t\t%.2f\n", current->boughtGood->numberOfRatings == 0 ? 0 : (float)(current->boughtGood->sumOfRates / current->boughtGood->numberOfRatings));
                printf("Seller Username:\t%s\n", current->boughtGood->seller->username);
                printf("\nYou %s\n", current->rated == BUYERRATED ? "rated this Good" : "Did not rate this Good");
            }
            current = current->next;
        }
        if (thisUserBasket == 0)
        {
            printf("you have no purchases!");
        }
    }
    else if (!strcmp(loggedinUser->userType, "seller"))
    {
        int thisUserGoods = 0;
        struct good *current = goodsHead->next;
        while (current != NULL)
        {
            if (!strcmp(current->seller->username, loggedinUser->username) && current->status != GOODDELETED)
            {
                thisUserGoods++;
                printf("----\n");
                printf("Good Name:\t\t%s\n", current->goodName);
                printf("Good Price:\t\t%d\n", current->goodPrice);
                printf("Good Count:\t\t%d\n", current->goodCount);
                printf("Good Rate:\t\t%.2f\n", current->numberOfRatings == 0 ? 0 : (float)(current->sumOfRates / current->numberOfRatings));
            }
            current = current->next;
        }
        if (thisUserGoods == 0)
            printf("you have no goods!");
    }

    free(input);
}
