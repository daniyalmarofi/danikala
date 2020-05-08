#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user
{
    char *username;
    char *password;
    char *userType;
    int deposit;
};

struct good
{
    int sellerId;
    char *goodName;
    int goodPrice;
    int goodCount;
};

struct buyerCart
{
    int buyerId;
    int goodId;
    int boughtCount;
};

void checkMalloc(void *pointer)
{
    if (pointer == NULL)
    {
        printf("Memory Allocation Error!");
        exit(EXIT_FAILURE);
    }
}

int checkInput(void *pointer)
{
    if (pointer == NULL)
    {
        printf("Wrong Input! Try again.");
        return 1;
    }
    return 0;
}

char *getCommandLine()
{
    char *str;
    int ch;
    size_t size = 1;
    size_t len = 0;
    str = (char *)realloc(NULL, sizeof(char) * size);
    checkMalloc(str);
    while (EOF != (ch = getchar()) && ch != '\n')
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

void doSignup(char *input, int *numberOfUsers, struct user **users)
{
    // getting and checking username and password and usertype from input
    char *username = strtok(NULL, " ");
    if (checkInput(username))
    {
        free(input);
        return;
    }
    char *password = strtok(NULL, " ");
    if (checkInput(password))
    {
        free(input);
        return;
    }
    char *userType = strtok(NULL, " ");
    if (checkInput(userType))
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

    if (strcmp(userType, "buyer") && strcmp(userType, "seller"))
    {
        printf("Undefined User Type!");
        free(input);
        return;
    }

    // search for the username and usertype for not existing
    int usernameExists = 0;
    int i = 0;
    while (i < *numberOfUsers && *numberOfUsers > 0)
    {
        if (!strcmp((*users)[i].username, username) && !strcmp((*users)[i].userType, userType))
        {
            usernameExists = 1;
            printf("this username is taken. Please try another.");
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

        free(input);

        (*numberOfUsers)++;
        (*users) = (struct user *)realloc((*users), *numberOfUsers * sizeof(struct user));
        checkMalloc((*users));

        (*users)[*numberOfUsers - 1].username = newUsername;
        (*users)[*numberOfUsers - 1].password = newPassword;
        (*users)[*numberOfUsers - 1].deposit = 0;
        (*users)[*numberOfUsers - 1].userType = newUserType;
        printf("user signed up.");
    }
    return;
}

void doLogin(char *input, int numberOfUsers, struct user *users, int *loggedinUserId)
{

    // getting and checking username and password and usertype from input
    char *username = strtok(NULL, " ");
    if (checkInput(username))
    {
        free(input);
        return;
    }

    char *password = strtok(NULL, " ");
    if (checkInput(password))
    {
        free(input);
        return;
    }

    char *userType = strtok(NULL, " ");
    if (checkInput(userType))
    {
        free(input);
        return;
    }

    if (strcmp(userType, "buyer") && strcmp(userType, "seller"))
    {
        printf("Undefined User Type!");
        free(input);
        return;
    }

    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    // checking if user exists based on username and password and usertype
    int i = 0;
    while (i < numberOfUsers && numberOfUsers > 0)
    {
        if (!strcmp(users[i].username, username) && !strcmp(users[i].password, password) && !strcmp(users[i].userType, userType))
        {
            *loggedinUserId = i;
            printf("%s! Welcome to your dashboard!", users[i].username);
            break;
        }
        i++;
    }

    if (*loggedinUserId == -1)
    {
        printf("the login is invalid!");
    }
    free(input);
    return;
}

void doLogout(char *input, int *loggedinUserId)
{
    if (strtok(NULL, " ") != NULL)
    {
        printf("too much input arguments!");
        free(input);
        return;
    }

    *loggedinUserId = -1;
    printf("user Logged out!");
    free(input);
}

int main()
{

    printf("Welcome To DaniKala!");
    int numberOfUsers = 0;
    struct user *users = NULL;
    int numberOfGoods = 0;
    struct good *goods = NULL;
    char *command;
    int loggedinUserId = -1;
    int buyerCartCount = 0;
    struct buyerCart *buyerCart = NULL;

    while (1)
    {
        // gettng input from user and checking for the entered command
        printf("\nEnter your Command:");
        char *input = getCommandLine();
        checkMalloc(input);
        command = strtok(input, " ");

        if (!strcmp(command, "signup") && loggedinUserId == -1)
        {
            doSignup(input, &numberOfUsers, &users);
        }
        else if (!strcmp(command, "login") && loggedinUserId == -1)
        {
            doLogin(input, numberOfUsers, users, &loggedinUserId);
        }
        else if (!strcmp(command, "logout") && loggedinUserId != -1)
        {
            doLogout(input, &loggedinUserId);
        }
        else if (!strcmp(command, "view") && loggedinUserId != -1)
        {
            if (strtok(NULL, " ") != NULL)
            {
                printf("too much input arguments!");
                free(input);
                continue;
            }

            printf("Displaying user Information:\n");
            printf("username: %s\t", users[loggedinUserId].username);
            printf("userType: %s\t", users[loggedinUserId].userType);
            printf("Deposit: %d\n", users[loggedinUserId].deposit);

            if (!strcmp(users[loggedinUserId].userType, "buyer"))
            {
                int thisUserBasket = 0;
                for (int i = 0; i < buyerCartCount; i++)
                {
                    if (buyerCart[i].buyerId == loggedinUserId)
                    {
                        thisUserBasket++;
                        printf("----\n");
                        printf("Good Name:\t\t%s\n", goods[buyerCart[i].goodId].goodName);
                        printf("Good Price:\t\t%d\n", goods[buyerCart[i].goodId].goodPrice);
                        printf("Bought Count:\t\t%d\n", buyerCart[i].boughtCount);
                        printf("Seller Username:\t%s\n", users[goods[buyerCart[i].goodId].sellerId].username);
                    }
                }
                if (thisUserBasket == 0)
                {
                    printf("you have no purchases!");
                }
            }
            else if (!strcmp(users[loggedinUserId].userType, "seller"))
            {
                int thisUserGoods = 0;
                for (int i = 0; i < numberOfGoods; i++)
                {
                    if (goods[i].sellerId == loggedinUserId)
                    {
                        thisUserGoods++;
                        printf("----\n");
                        printf("Good Name:\t\t%s\n", goods[i].goodName);
                        printf("Good Price:\t\t%d\n", goods[i].goodPrice);
                        printf("Good Count:\t\t%d\n", goods[i].goodCount);
                    }
                }
                if (thisUserGoods == 0)
                {
                    printf("you have no goods!");
                }
            }

            free(input);
        }
        else if (!strcmp(command, "deposit") && loggedinUserId != -1 && !strcmp(users[loggedinUserId].userType, "buyer"))
        {
            if (strtok(NULL, " ") != NULL)
            {
                printf("too much input arguments!");
                free(input);
                continue;
            }
            // get the deposit value and convert it to integer and add it to user deposit
            char *deposit = strtok(NULL, " ");
            int depositvalue = 0;
            if (checkInput(deposit))
                continue;
            if ((depositvalue = atoi(deposit)) > 0)
            {
                users[loggedinUserId].deposit += depositvalue;
                printf("%d successfuly added to your deposit.\nNow your deposit is %d.", depositvalue, users[loggedinUserId].deposit);
            }
            else
                printf("Wrong input! Try again!");

            free(input);
        }
        else if (!strcmp(command, "add_goods") && loggedinUserId != -1 && !strcmp(users[loggedinUserId].userType, "seller"))
        {
            if (strtok(NULL, " ") != NULL)
            {
                printf("too much input arguments!");
                free(input);
                continue;
            }

            // getting and checking goodName and goodPrice and goodCount from input
            char *sellerUsername = strtok(NULL, " ");
            if (checkInput(sellerUsername))
            {
                free(input);
                continue;
            }
            char *goodName = strtok(NULL, " ");
            if (checkInput(goodName))
            {
                free(input);
                continue;
            }
            char *goodPrice = strtok(NULL, " ");
            if (checkInput(goodPrice))
            {
                free(input);
                continue;
            }
            char *goodCount = strtok(NULL, " ");
            if (checkInput(goodCount))
            {
                free(input);
                continue;
            }
            int goodPriceValue = atoi(goodPrice);
            int goodCountValue = atoi(goodCount);
            if (goodPriceValue <= 0 || goodCountValue <= 0)
            {
                printf("Wrong Input! Try again!");
                free(input);
                continue;
            }

            if (strcmp(sellerUsername, users[loggedinUserId].username))
            {
                printf("you can not add or chnge count of this good!");
                free(input);
                continue;
            }

            // search for the goodName for not existing
            // if good exists I'd assign the id of that good to goodExists Variable
            int goodExists = -1;
            int i = 0;
            while (i < numberOfGoods && numberOfGoods > 0)
            {
                if (!strcmp(goods[i].goodName, goodName))
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

                free(input);

                numberOfGoods++;
                goods = (struct good *)realloc(goods, numberOfGoods * sizeof(struct good));
                checkMalloc(goods);

                goods[numberOfGoods - 1].sellerId = loggedinUserId;
                goods[numberOfGoods - 1].goodName = newGoodname;
                goods[numberOfGoods - 1].goodPrice = goodPriceValue;
                goods[numberOfGoods - 1].goodCount = goodCountValue;

                printf("Good Successfully added.");
            }
            else
            {
                if (!strcmp(users[goods[goodExists].sellerId].username, users[loggedinUserId].username))
                {
                    goods[goodExists].goodCount = goodCountValue;
                    printf("goodCount changed!");
                }
                else
                    printf("you are not the seller of this good!");

                free(input);
            }
        }
        else if (!strcmp(command, "show_goods") && loggedinUserId != -1)
        {
            if (strtok(NULL, " ") != NULL)
            {
                printf("too much input arguments!");
                free(input);
                continue;
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
        else if (!strcmp(command, "buy") && loggedinUserId != -1 && !strcmp(users[loggedinUserId].userType, "buyer"))
        {
            if (strtok(NULL, " ") != NULL)
            {
                printf("too much input arguments!");
                free(input);
                continue;
            }

            // getting and checking goodName and goodPrice and goodCount from input
            char *goodName = strtok(NULL, " ");
            if (checkInput(goodName))
            {
                free(input);
                continue;
            }
            char *goodCount = strtok(NULL, " ");
            if (checkInput(goodCount))
            {
                free(input);
                continue;
            }
            char *goodSellerUsername = strtok(NULL, " ");
            if (checkInput(goodSellerUsername))
            {
                free(input);
                continue;
            }
            int goodCountValue = atoi(goodCount);
            if (goodCountValue <= 0)
            {
                printf("Wrong Input! Try again!");
                free(input);
                continue;
            }

            // search for the goodName for not existing
            // if good exists I'd assign the id of that good to goodExists Variable
            int goodExists = -1;
            int i = 0;
            while (i < numberOfGoods && numberOfGoods > 0)
            {
                if (!strcmp(goods[i].goodName, goodName))
                {
                    goodExists = i;
                    break;
                }
                i++;
            }

            // if good exists do the buying
            if (goodExists > -1)
            {
                if (goods[goodExists].goodCount < goodCountValue)
                {
                    printf("requested count is more than good count");
                    free(input);
                    continue;
                }
                if ((goods[goodExists].goodPrice) * goodCountValue > users[loggedinUserId].deposit)
                {
                    printf("you can not afford this good.");
                    free(input);
                    continue;
                }
                goods[goodExists].goodCount -= goodCountValue;
                users[loggedinUserId].deposit -= (goods[goodExists].goodPrice) * goodCountValue;
                users[goods[goodExists].sellerId].deposit += (goods[goodExists].goodPrice) * goodCountValue;

                free(input);

                buyerCartCount++;
                buyerCart = (struct buyerCart *)realloc(buyerCart, buyerCartCount * sizeof(struct buyerCart));
                checkMalloc(buyerCart);

                buyerCart[buyerCartCount - 1].buyerId = loggedinUserId;
                buyerCart[buyerCartCount - 1].goodId = goodExists;
                buyerCart[buyerCartCount - 1].boughtCount = goodCountValue;

                printf("The good bought successfuly!");
            }
            else
            {
                printf("this good does not exists!");
                free(input);
            }
        }
        else if (!strcmp(command, "exit"))
        {
            if (strtok(NULL, " ") != NULL)
            {
                printf("too much input arguments!");
                free(input);
                continue;
            }

            break;
            free(input);
        }
        else
        {
            printf("Command Not Found!");
            free(input);
        }
    }

    // clearing all allocated momries
    for (int i = 0; i < numberOfUsers; i++)
    {
        free(users[i].username);
        free(users[i].password);
        free(users[i].userType);
    }
    free(users);

    for (int i = 0; i < numberOfGoods; i++)
    {
        free(goods[i].goodName);
    }
    free(goods);

    free(buyerCart);

    free(users);
    return 0;
}
