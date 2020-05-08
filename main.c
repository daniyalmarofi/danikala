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

int main()
{

    printf("Welcome To DaniKala!");
    int numberOfUsers = 0;
    struct user *users = NULL;
    int numberOfGoods = 0;
    struct good *goods = NULL;
    char *command;
    int loggedinUserId = -1;
    int buyerBasketCount = 0;
    int *buyerBasket = NULL;

    while (1)
    {
        // gettng input from user and checking for the entered command
        printf("\nEnter your Command:");
        char *input = getCommandLine();
        checkMalloc(input);
        command = strtok(input, " ");

        // TODO add exception: signup sdkjfhs skjdfhsjkd skdjhfjskd sjdkhfsjf skjdhfkjsdf(more than expected arguments) to all commands
        if (!strcmp(command, "signup") && loggedinUserId == -1)
        {
            // getting and checking username and password and usertype from input
            char *username = strtok(NULL, " ");
            if (checkInput(username))
            {
                free(input);
                continue;
            }
            char *password = strtok(NULL, " ");
            if (checkInput(password))
            {
                free(input);
                continue;
            }
            char *userType = strtok(NULL, " ");
            if (checkInput(password))
            {
                free(input);
                continue;
            }

            if (strcmp(userType, "buyer") && strcmp(userType, "seller"))
            {
                printf("Undefined User Type!");
                free(input);
                continue;
            }

            // search for the username and usertype for not existing
            int usernameExists = 0;
            int i = 0;
            while (i < numberOfUsers && numberOfUsers > 0)
            {
                if (!strcmp(users[i].username, username) && !strcmp(users[i].userType, userType))
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

                numberOfUsers++;
                users = (struct user *)realloc(users, numberOfUsers * sizeof(struct user));
                checkMalloc(users);

                users[numberOfUsers - 1].username = newUsername;
                users[numberOfUsers - 1].password = newPassword;
                users[numberOfUsers - 1].deposit = 0;
                users[numberOfUsers - 1].userType = newUserType;
                printf("user signed up.");
            }
        }
        else if (!strcmp(command, "login") && loggedinUserId == -1)
        {
            // getting and checking username and password and usertype from input
            char *username = strtok(NULL, " ");
            if (checkInput(username))
            {
                free(input);
                continue;
            }

            char *password = strtok(NULL, " ");
            if (checkInput(password))
            {
                free(input);
                continue;
            }

            char *userType = strtok(NULL, " ");
            if (checkInput(userType))
            {
                free(input);
                continue;
            }

            if (strcmp(userType, "buyer") && strcmp(userType, "seller"))
            {
                printf("Undefined User Type!");
                free(input);
                continue;
            }

            // checking if user exists based on username and password and usertype
            int i = 0;
            while (i < numberOfUsers && numberOfUsers > 0)
            {
                if (!strcmp(users[i].username, username) && !strcmp(users[i].password, password) && !strcmp(users[i].userType, userType))
                {
                    loggedinUserId = i;
                    printf("%s! Welcome to your dashboard!", users[i].username);
                    break;
                }
                i++;
            }

            if (loggedinUserId == -1)
            {
                printf("the login is invalid!");
            }
            free(input);
        }
        else if (!strcmp(command, "logout") && loggedinUserId != -1)
        {
            loggedinUserId = -1;
            printf("user Logged out!");
            free(input);
        }
        else if (!strcmp(command, "view") && loggedinUserId != -1)
        {
            printf("Displaying user Information:\n");
            printf("username: %s\t", users[loggedinUserId].username);
            printf("userType: %s\t", users[loggedinUserId].userType);
            printf("Deposit: %s\t", users[loggedinUserId].deposit);
            // TODO add user sells or boughts
            free(input);
        }
        else if (!strcmp(command, "deposit") && loggedinUserId != -1 && !strcmp(users[loggedinUserId].userType, "buyer"))
        {
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
            // getting and checking goodName and goodPrice and goodCount from input
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

            // search for the goodName for not existing
            // if good exists I'd assign the id of that good to goodExists Variable
            int goodExists = 0;
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
            if (!goodExists)
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
            printf("Showing all goods of DaniKala!\n");
            for (int i = 0; i < numberOfGoods; i++)
            {
                printf("----\n");
                printf("Seller Username:\t%s\n", users[goods[i].sellerId].username);
                printf("Good Name:\t%s\n", goods[i].goodName);
                printf("Good Price:\t%d\n", goods[i].goodPrice);
                printf("Good Count:\t%d\n", goods[i].goodCount);
            }
            free(input);
        }
        else if (!strcmp(command, "buy") && loggedinUserId != -1 && !strcmp(users[loggedinUserId].userType, "buyer")){
            // doing something!
        }
        else if (!strcmp(command, "exit"))
        {
            break;
            free(input);
        }
        else
        {
            printf("Command Not Found!");
            free(input);
        }
    }

    // TODO add a for loop to clear all allocated momries
    free(users);
    return 0;
}
