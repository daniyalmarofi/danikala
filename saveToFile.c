#ifndef HEADERS_IMPORTED
#include "commonFunctions.h"
#include "main.h"
#endif

//** This Function saves the users array to defined USERSFILE .txt file
void saveUsers(int numberOfUsers, struct user *users)
{
    FILE *fp;

    fp = fopen(USERS_FILE, "w");
    if (fp == NULL)
        return;

    // loop to users array and save each to file
    int i = 0;
    while (i < numberOfUsers && numberOfUsers > 0)
    {
        fprintf(fp, "%s, %s, %s, %d\n", users[i].username, users[i].password,
                users[i].userType, users[i].deposit);
        i++;
    }
    fclose(fp);
}

//** This Function saves the goods array to defined GOODSFILE .txt file
void saveGoods(int numberOfGoods, struct good *goods)
{
    FILE *fp;

    fp = fopen(GOODS_FILE, "w");
    if (fp == NULL)
        return;

    // loop to goods array and save each to file
    int i = 0;
    while (i < numberOfGoods && numberOfGoods > 0)
    {
        fprintf(fp, "%d, %s, %d, %d\n", goods[i].sellerId, goods[i].goodName,
                goods[i].goodPrice, goods[i].goodCount);
        i++;
    }
    fclose(fp);
}

//** This Function saves the buyerCart array to defined BUYHISTORYFILE .txt file
void saveHistory(int buyerCartCount, struct buyerCart *buyerCart)
{
    FILE *fp;

    fp = fopen(BUY_HISTORY_FILE, "w");
    if (fp == NULL)
        return;

    // loop to goods array and save each to file
    int i = 0;
    while (i < buyerCartCount && buyerCartCount > 0)
    {
        fprintf(fp, "%d, %d, %d\n", buyerCart[i].buyerId, buyerCart[i].goodId,
                buyerCart[i].boughtCount);
        i++;
    }
    fclose(fp);
}