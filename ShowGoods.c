#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function shows all the goods for all users
void doShowGoods(char* input, struct good* goods, int numberOfGoods, struct user* users)
{

    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    printf("Showing all goods of DaniKala!\n");
    for (int i = 0; i < numberOfGoods; i++)
    {
        printf("----\n");
        printf("Seller Username:\t%s\n", users[goods[i].sellerId].username);
        printf("Good Name:\t\t%s\n", goods[i].goodName);
        printf("Good Price:\t\t%d\n", goods[i].goodPrice);
        printf("Good Count:\t\t%d\n", goods[i].goodCount);
    }
    free(input);
}
