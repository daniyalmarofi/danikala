#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif
#include "SortGoods.c"
#include "SortGoods.h"

void doSearch(char *input, struct good *goodsHead)
{

    // getting and checking goodName and seller username and rate from input

    char *numberOfConditions = strtok(NULL, " ");
    if (checkInput(numberOfConditions))
    {
        free(input);
        return;
    }
    int numberOfConditionsValue = atoi(numberOfConditions);

    free(input);
    if (numberOfConditionsValue > 4 || numberOfConditionsValue < 1)
    {
        printf("Wrong Input! Try again!");
        return;
    }

    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        return;
    }

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
            strcpy(name, nameSearch);
        }
        else if (!strcmp(Condition, "seller_username"))
        {
            char *name = (char *)malloc(sizeof(char) * strlen(value));
            checkMalloc(name);
            strcpy(name, sellerUsernameSearch);
        }
        else if (!strcmp(Condition, "min_price") && isdigit(value))
        {
            minPriceSearch = atoi(value);
        }
        else if (!strcmp(Condition, "max_price") && isdigit(value))
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

        if (!(minPriceSearch > 0 || maxPriceSearch > 0))
        {
            printf("Wrong Input. Try again!");
            return;
        }
    }

    return;
}