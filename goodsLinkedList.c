#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** This Function gets the head and goods data and adds a new node at the end of the list
void addGood(struct good *goodsHead, struct user *seller, char *goodName, int goodPrice, int goodCount, int status)
{
    // find the last node
    struct good *last = goodsHead;
    while (last->next != NULL)
        last = last->next;

    // define the last node
    struct good *newGood = (struct good *)malloc(sizeof(struct good));
    checkMalloc(newGood);
    newGood->seller = seller;
    newGood->goodName = goodName;
    newGood->goodPrice = goodPrice;
    newGood->goodCount = goodCount;
    newGood->status = status;
    newGood->numberOfRatings = 0;
    newGood->sumOfRates = 0;
    newGood->next = NULL;

    // add new good at the end of the list
    last->next = newGood;
    return;
}

//** This Function gets the head and goodname and returns the pointer to that node
struct good *findGood(struct good *goodsHead, char *goodName)
{
    // searching for the good
    struct good *current = goodsHead->next;
    while (current != NULL)
    {
        if (!strcmp(current->goodName, goodName))
            return current;
        current = current->next;
    }
    return NULL;
}