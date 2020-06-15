#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif
#include "SortGoods.c"
#include "SortGoods.h"

//** this function shows all the goods for all users
void doShowGoods(char *input, struct good *goodsHead)
{
    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    // sorting the goods Linked List
    sortGoods(goodsHead);
    printf("Showing all goods of DaniKala!\n");
    struct good *current = goodsHead->next;
    int goodsCount = 0;
    while (current != NULL)
    {
        if (current->status != GOOD_DELETED)
        {
            goodsCount++;
            printf("----\n");
            printf("Seller Username:\t%s\n", current->seller->username);
            printf("Good Name:\t\t%s\n", current->goodName);
            printf("Good Price:\t\t%d\n", current->goodPrice);
            printf("Good Count:\t\t%d\n", current->goodCount);
            if (current->numberOfRatings == 0)
                printf("Good Rate:\t\tNaN\n");
            else
                printf("Good Rate:\t\t%.2f\n", (float)(current->sumOfRates / current->numberOfRatings));
        }
        current = current->next;
    }

    if (goodsCount == 0)
    {
        printf("Nothing Found!");
    }

    free(input);
}
