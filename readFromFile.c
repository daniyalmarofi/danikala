#ifndef HEADERS_IMPORTED
#include "commonFunctions.h"
#include "main.h"
#endif

//** this function gets a line from the file specified by FILE *fp
char *getFileLine(FILE *fp)
{
    char *str;
    int ch;
    size_t size = 1;
    size_t len = 0;
    str = (char *)realloc(NULL, sizeof(char) * size);
    checkMalloc(str);
    while (EOF != (ch = fgetc(fp)) && ch != '\n')
    {
        str[len++] = ch;
        if (len == size)
        {
            str = (char *)realloc(str, sizeof(char) * (size += 16));
            checkMalloc(str);
        }
    }
    str[len++] = '\0';

    return (char *)realloc(str, sizeof(char) * len);
}

//** This Function reads the users array from defined USERSFILE .txt file
void readUsers(int *numberOfUsers, struct user **users)
{
    FILE *fp;

    fp = fopen(USERSFILE, "r");
    if (fp == NULL)
        return;

    char *line;

    while ((line = getFileLine(fp)) && *line != NULL)
    {
        // getting and checking username and password and usertype from line
        char *username = strtok(line, ", ");
        if (checkInput(username))
        {
            free(line);
            continue;
        }
        char *password = strtok(NULL, ", ");
        if (checkInput(password))
        {
            free(line);
            continue;
        }
        char *userType = strtok(NULL, ", ");
        if (checkInput(userType))
        {
            free(line);
            continue;
        }
        char *depositChar = strtok(NULL, ", ");
        if (checkInput(depositChar))
        {
            free(line);
            continue;
        }
        int deposit = atoi(depositChar);

        if (strtok(NULL, " ") != NULL)
        {
            printf("\nError reading from users file: too much input arguments!");
            free(line);
            continue;
        }

        if (strcmp(userType, "buyer") && strcmp(userType, "seller"))
        {
            printf("\nError reading from users file: Undefined User Type!");
            free(line);
            continue;
        }

        // search for the username and usertype for not existing
        int usernameExists = 0;
        int i = 0;
        while (i<*numberOfUsers && * numberOfUsers> 0)
        {
            if (!strcmp((*users)[i].username, username) && !strcmp((*users)[i].userType, userType))
            {
                usernameExists = 1;
                printf("\nError reading from users file: this username is taken: %s, %s", username, userType);
                break;
            }
            i++;
        }

        // if newuser does not exists add it to user
        if (!usernameExists)
        {
            char *newUsername = (char *)malloc(sizeof(char) * strlen(username));
            checkMalloc(newUsername);
            strcpy(newUsername, username);

            char *newPassword = (char *)malloc(sizeof(char) * strlen(password));
            checkMalloc(newPassword);
            strcpy(newPassword, password);

            char *newUserType = (char *)malloc(sizeof(char) * strlen(userType));
            checkMalloc(newUserType);
            strcpy(newUserType, userType);

            free(line);

            (*numberOfUsers)++;
            (*users) = (struct user *)realloc((*users), *numberOfUsers * sizeof(struct user));
            checkMalloc((*users));

            (*users)[*numberOfUsers - 1].username = newUsername;
            (*users)[*numberOfUsers - 1].password = newPassword;
            (*users)[*numberOfUsers - 1].deposit = deposit;
            (*users)[*numberOfUsers - 1].userType = newUserType;
        }
    }

    fclose(fp);
    printf("\nsuccessfully imported users data.");
}

//** This Function reads the goods array from defined GOODSFILE .txt file
void readGoods(int *numberOfGoods, struct good **goods, int numberOfUsers, struct user *users)
{
    FILE *fp;

    fp = fopen(GOODSFILE, "r");
    if (fp == NULL)
        return;

    char *line;

    while ((line = getFileLine(fp)) && *line != NULL)
    {
        // getting and checking goodName and goodPrice and goodCount from file
        char *sellerUserIdChar = strtok(line, ", ");
        if (checkInput(sellerUserIdChar))
        {
            free(line);
            continue;
        }
        char *goodName = strtok(NULL, ", ");
        if (checkInput(goodName))
        {
            free(line);
            continue;
        }
        char *goodPrice = strtok(NULL, ", ");
        if (checkInput(goodPrice))
        {
            free(line);
            continue;
        }
        char *goodCount = strtok(NULL, ", ");
        if (checkInput(goodCount))
        {
            free(line);
            continue;
        }

        if (strtok(NULL, ", ") != NULL)
        {
            printf("\nError reading from goods file: too much input arguments!");
            free(line);
            continue;
        }

        int goodSellerId = atoi(sellerUserIdChar);
        int goodPriceValue = atoi(goodPrice);
        int goodCountValue = atoi(goodCount);
        if (goodSellerId < 0 || goodPriceValue <= 0 || goodCountValue <= 0)
        {
            printf("Error reading from goods file: Wrong Input!");
            free(line);
            continue;
        }

        // search for the goodName for not existing
        // if good exists I'd assign the id of that good to goodExists Variable
        int goodExists = -1;
        int i = 0;
        while (i<*numberOfGoods && * numberOfGoods> 0)
        {
            if (!strcmp((*goods)[i].goodName, goodName))
            {
                goodExists = i;
                break;
            }
            i++;
        }

        // check if the buyer exists
        // if buyer exists I'd assign the id of that buyer to buyerExists Variable
        int buyerExists = -1;
        if (goodSellerId < numberOfUsers && !strcmp(users[goodSellerId].userType, "seller"))
        {
            buyerExists = goodSellerId;
        }

        // if new Good does not exists add it to goods
        if (goodExists = -1 && buyerExists > -1)
        {
            char *newGoodname = (char *)malloc(sizeof(char) * strlen(goodName));
            checkMalloc(newGoodname);
            strcpy(newGoodname, goodName);

            free(line);

            (*numberOfGoods)++;
            *goods = (struct good *)realloc(*goods, *numberOfGoods * sizeof(struct good));
            checkMalloc(*goods);

            (*goods)[*numberOfGoods - 1].sellerId = goodSellerId;
            (*goods)[*numberOfGoods - 1].goodName = newGoodname;
            (*goods)[*numberOfGoods - 1].goodPrice = goodPriceValue;
            (*goods)[*numberOfGoods - 1].goodCount = goodCountValue;
        }
        else
        {
            printf("\nError reading from goods file:  this good exists! or this seller does not exists!");

            free(line);
        }
    }

    fclose(fp);
    printf("\nsuccessfully imported goods data.");
}

//** This Function reads the history array from defined BUYHISTORYFILE .txt file
void readHistory(int *buyerCartCount, struct buyerCart **buyerCart, int numberOfGoods, struct good *goods, int numberOfUsers, struct user *users)
{
    FILE *fp;

    fp = fopen(BUYHISTORYFILE, "r");
    if (fp == NULL)
        return;

    char *line;

    while ((line = getFileLine(fp)) && *line != NULL)
    {
        // getting and checking goodName and goodPrice and goodCount from input
        char *buyerIdChar = strtok(line, ", ");
        if (checkInput(buyerIdChar))
        {
            free(line);
            return;
        }
        char *goodIdChar = strtok(NULL, ", ");
        if (checkInput(goodIdChar))
        {
            free(line);
            return;
        }
        char *boughtCountChar = strtok(NULL, ", ");
        if (checkInput(boughtCountChar))
        {
            free(line);
            return;
        }

        int buyerId = atoi(buyerIdChar);
        int goodId = atoi(goodIdChar);
        int boughtCount = atoi(boughtCountChar);
        if (buyerId < 0 || goodId < 0 || boughtCount <= 0)
        {
            printf("\nError reading from history file: Wrong Input!");
            free(line);
            continue;
        }

        if (strtok(NULL, ", ") != NULL)
        {
            printf("\nError reading from history file: too much input arguments!");
            free(line);
            return;
        }

        // check if the good exists
        // if good exists I'd assign the id of that good to goodExists Variable
        int goodExists = -1;
        if (goodId < numberOfGoods)
        {
            goodExists = goodId;
        }

        // check if the buyer exists
        // if buyer exists I'd assign the id of that buyer to buyerExists Variable
        int buyerExists = -1;
        if (buyerId < numberOfUsers && !strcmp(users[buyerId].userType, "buyer"))
        {
            buyerExists = buyerId;
        }

        // if good exists do the buying
        if (goodExists > -1 && buyerExists > -1)
        {
            free(line);

            (*buyerCartCount)++;
            *buyerCart = (struct buyerCart *)realloc(*buyerCart, *buyerCartCount * sizeof(struct buyerCart));
            checkMalloc(buyerCart);

            (*buyerCart)[*buyerCartCount - 1].buyerId = buyerExists;
            (*buyerCart)[*buyerCartCount - 1].goodId = goodExists;
            (*buyerCart)[*buyerCartCount - 1].boughtCount = boughtCount;
        }
        else
        {
            printf("\nError reading from history file: this good or buyer does not exists!");
            free(line);
        }
    }

    fclose(fp);
    printf("\nsuccessfully imported history data.");
}