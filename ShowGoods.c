#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function shows all the goods for all users
void doShowGoods(char *input, struct good *goodsHead)
{

    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    printf("Showing all goods of DaniKala!\n");
    struct good *current = goodsHead->next;
    while (current != NULL)
    {
        if (current->status != GOODDELETED)
        {
            printf("----\n");
            printf("Seller Username:\t%s\n", current->seller->username);
            printf("Good Name:\t\t%s\n", current->goodName);
            printf("Good Price:\t\t%d\n", current->goodPrice);
            printf("Good Count:\t\t%d\n", current->goodCount);
            printf("Good Rate:\t\t%.2f\n", current->numberOfRatings == 0 ? 0 : (float)(current->sumOfRates / current->numberOfRatings));
        }
        current = current->next;
    }
    free(input);
}
