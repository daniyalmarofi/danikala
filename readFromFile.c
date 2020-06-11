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

    char *line;

    while ((line = getFileLine(fp)) && *line != NULL)
    {
        // getting and checking username and password and usertype from line
        char *username = strtok(line, ", ");
        if (checkInput(username))
        {
            free(line);
            return;
        }
        char *password = strtok(NULL, ", ");
        if (checkInput(password))
        {
            free(line);
            return;
        }
        char *userType = strtok(NULL, ", ");
        if (checkInput(userType))
        {
            free(line);
            return;
        }
        char *depositChar = strtok(NULL, ", ");
        if (checkInput(depositChar))
        {
            free(line);
            return;
        }
        int deposit = atoi(depositChar);

        if (strtok(NULL, " ") != NULL)
        {
            printf("\nError reading from users file: too much input arguments!");
            free(line);
            return;
        }

        if (strcmp(userType, "buyer") && strcmp(userType, "seller"))
        {
            printf("\nError reading from users file: Undefined User Type!");
            free(line);
            return;
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
}

//** This Function reads the goods array from defined GOODSFILE .txt file
void readGoods(int *numberOfGoods, struct good **goods)
{
    FILE *fp;

    fp = fopen(GOODSFILE, "r");

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

        // if new Good does not exists add it to goods
        if (goodExists = -1)
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
            (*goods)[goodExists].goodCount = goodCountValue;

            free(line);
        }
    }

    fclose(fp);
}