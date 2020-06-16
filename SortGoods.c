#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this Function swaps the firstGood with secondGood
struct good *swapGoods(struct good *firstGood, struct good *secondGood)
{
    struct good *tmp = secondGood->next;
    secondGood->next = firstGood;
    firstGood->next = tmp;
    return secondGood;
}

//** this function sorts the goods LL using the count of LL to decrease Time Complexity
void bubbleSort(struct good **goodsHead, int goodsCount)
{
    struct good **headPointer;

    struct good *thisGood;
    struct good *nextGood;
    int i, j, swapped;

    for (i = 0; i <= goodsCount; i++)
    {
        headPointer = goodsHead;
        swapped = 0;

        for (j = 0; j < goodsCount - i - 1; j++)
        {
            struct good *thisGood = *headPointer;
            struct good *nextGood = thisGood->next;

            if (strcmp(thisGood->goodName, nextGood->goodName) > 0)
            {
                // swap the goods
                *headPointer = swapGoods(thisGood, nextGood);
                swapped = 1;
            }

            headPointer = &((*headPointer)->next);
        }

        /* break if the loop ended without any swap */
        if (swapped == 0)
            break;
    }
    return;
}

//** this function sorts the goods Linked List using bubble sort
void sortGoods(struct good *goodsHead)
{
    // count the number of nodes
    int n = 0;
    struct good *thisGood = goodsHead->next;
    while (thisGood != NULL)
    {
        n++;
        thisGood = thisGood->next;
    }

    // sort the goods using bubble sort
    bubbleSort(&(goodsHead->next), n);

    return;
}