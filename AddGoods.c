#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function adds a good the store
void doAddGoods(char* input, struct user* loggedinUser, struct good** goods, int* numberOfGoods)
{
    // getting and checking goodName and goodPrice and goodCount from input
    char* sellerUsername = strtok(NULL, " ");
    if (checkInput(sellerUsername))
    {
        free(input);
        return;
    }
    char* goodName = strtok(NULL, " ");
    if (checkInput(goodName))
    {
        free(input);
        return;
    }
    char* goodPrice = strtok(NULL, " ");
    if (checkInput(goodPrice))
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

    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    int goodPriceValue = atoi(goodPrice);
    int goodCountValue = atoi(goodCount);
    if (goodPriceValue <= 0 || goodCountValue <= 0)
    {
        printf("Wrong Input! Try again!");
        free(input);
        return;
    }

    if (strcmp(sellerUsername, users[loggedinUserId].username))
    {
        printf("you can not add or chnge count of this good!");
        free(input);
        return;
    }

    // search for the goodName for not existing
    // if good exists I'd assign the id of that good to goodExists Variable
    int goodExists = -1;
    int i = 0;
    while (i < *numberOfGoods && *numberOfGoods> 0)
    {
        if (!strcmp((*goods)[i].goodName, goodName))
        {
            goodExists = i;
            break;
        }
        i++;
    }

    // if new Good does not exists add it to goods
    if (goodExists = -1)
    {
        char* newGoodname = (char*)malloc(sizeof(char) * strlen(goodName));
        checkMalloc(newGoodname);
        strcpy(newGoodname, goodName);

        free(input);

        (*numberOfGoods)++;
        *goods = (struct good*)realloc(*goods, *numberOfGoods * sizeof(struct good));
        checkMalloc(*goods);

        (*goods)[*numberOfGoods - 1].sellerId = loggedinUserId;
        (*goods)[*numberOfGoods - 1].goodName = newGoodname;
        (*goods)[*numberOfGoods - 1].goodPrice = goodPriceValue;
        (*goods)[*numberOfGoods - 1].goodCount = goodCountValue;

        printf("Good Successfully added.");
    }
    else
    {
        if (!strcmp(users[(*goods)[goodExists].sellerId].username, users[loggedinUserId].username))
        {
            (*goods)[goodExists].goodCount = goodCountValue;
            printf("goodCount changed!");
        }
        else
            printf("you are not the seller of this good!");

        free(input);
    }
}
