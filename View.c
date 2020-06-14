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
                printf("Good Price:\t\t%d\n", current->boughtGood->goodPrice);
                printf("Bought Count:\t\t%d\n", current->boughtCount);
                printf("Seller Username:\t%s\n", current->boughtGood->seller->username);
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
            if (!strcmp(current->seller->username, loggedinUser->username))
            {
                thisUserGoods++;
                printf("----\n");
                printf("Good Name:\t\t%s\n", current->goodName);
                printf("Good Price:\t\t%d\n", current->goodPrice);
                printf("Good Count:\t\t%d\n", current->goodCount);
            }
            current = current->next;
        }
        if (thisUserGoods == 0)
            printf("you have no goods!");
    }

    free(input);
}
