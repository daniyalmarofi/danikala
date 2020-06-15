#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#include "goodsLinkedList.c"
#include "goodsLinkedList.h"
#include "SortGoods.c"
#include "SortGoods.h"
#endif

//** This function searches for the goods with the input name
struct good *searchName(struct good *goodsHead, char *goodName)
{
    // create the result LL
    struct good *searchedHead = (struct good *)malloc(sizeof(struct good));
    searchedHead->next = NULL;

    // search the goods for the condition
    struct good *current = goodsHead;
    while (current != NULL)
    {
        if (!strcmp(current->goodName, goodName) && current->status == GOOD_ACTIVE)
        {
            addGood(searchedHead, current->seller, current->goodName, current->goodPrice, current->goodCount, GOOD_ACTIVE);
        }
        current = current->next;
    }

    struct good *retLL = searchedHead->next;
    free(searchedHead);

    return retLL;
}

//** This function searches for the goods from the sellerUsername
struct good *searchSellerUsername(struct good *goodsHead, char *sellerUsername, int searchedOnce)
{
    // create the result LL
    struct good *searchedHead = (struct good *)malloc(sizeof(struct good));
    searchedHead->next = NULL;

    // search the goods for the condition
    struct good *current = goodsHead;
    while (current != NULL)
    {
        if (!strcmp(current->seller->username, sellerUsername) && current->status == GOOD_ACTIVE)
        {
            addGood(searchedHead, current->seller, current->goodName, current->goodPrice, current->goodCount, GOOD_ACTIVE);
        }
        struct good *temp = current->next;
        if (searchedOnce)
        {
            free(current->goodName);
            free(current);
        }
        current = temp;
    }

    struct good *retLL = searchedHead->next;
    free(searchedHead);

    return retLL;
}


//** this function does the search and shows the result
void searchAndShowResult(struct good *goodsHead, char *nameSearch, char *sellerUsernameSearch)
{
    // call the functions to search acoording to each condition
    struct good *searchingList = goodsHead->next;
    int searchedOnce = 0;
    if (nameSearch != NULL)
    {
        searchingList = searchName(searchingList, nameSearch);
        searchedOnce = 1;
    }
    if (sellerUsernameSearch != NULL)
    {
        searchingList = searchSellerUsername(searchingList, sellerUsernameSearch, searchedOnce);
        searchedOnce = 1;
    }

    // Now show the List
    printf("Showing all goods of DaniKala!\n");
    struct good *current = searchingList;
    while (current != NULL)
    {
        if (current->status != GOOD_DELETED)
        {
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
    return;
}

//** This Function does the search with 4 conditions
void doSearch(char *input, struct good *goodsHead)
{

    // getting and checking goodName and seller username and rate from input

    char *numberOfConditions = strtok(NULL, " ");
    if (checkInput(numberOfConditions))
    {
        free(input);
        return;
    }

    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    int numberOfConditionsValue = atoi(numberOfConditions);

    if (numberOfConditionsValue > 4 || numberOfConditionsValue < 1)
    {
        printf("Wrong Input! Try again!");
        free(input);
        return;
    }
    free(input);

    char *nameSearch = NULL;
    char *sellerUsernameSearch = NULL;
    int minPriceSearch = 0;
    int maxPriceSearch = 0;

    for (int i = 0; i < numberOfConditionsValue; i++)
    {
        // get the input and check wrong inputs
        input = getCommandLine();
        checkMalloc(input);
        char *Condition = strtok(input, " ");
        if (checkInput(Condition))
        {
            free(input);
            return;
        }
        char *value = strtok(NULL, " ");
        if (checkInput(value))
        {
            free(input);
            return;
        }

        if (strtok(NULL, " ") != NULL)
        {
            printf("too much input arguments!");
            free(input);
            return;
        }

        // checking the 4 conditions and get the values
        if (!strcmp(Condition, "name"))
        {
            char *name = (char *)malloc(sizeof(char) * strlen(value));
            checkMalloc(name);
            strcpy(name, value);
            nameSearch = name;
        }
        else if (!strcmp(Condition, "seller_username"))
        {
            char *name = (char *)malloc(sizeof(char) * strlen(value));
            checkMalloc(name);
            strcpy(name, value);
            sellerUsernameSearch = name;
        }
        else if (!strcmp(Condition, "min_price") && atoi(value) > 0)
        {
            minPriceSearch = atoi(value);
        }
        else if (!strcmp(Condition, "max_price") && atoi(value) > 0)
        {
            maxPriceSearch = atoi(value);
        }
        else
        {
            printf("Wrong Input. Try again!");
            free(input);
            return;
        }
        free(input);
    }

    searchAndShowResult(goodsHead, nameSearch, sellerUsernameSearch);

    return;
}
