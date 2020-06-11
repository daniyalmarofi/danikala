#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.c"
#include "commonFunctions.h"
#endif

#include "AddGoods.c"
#include "AddGoods.h"
#include "Buy.c"
#include "Buy.h"
#include "Deposit.c"
#include "Deposit.h"
#include "Login.c"
#include "Login.h"
#include "Logout.c"
#include "Logout.h"
#include "ShowGoods.c"
#include "ShowGoods.h"
#include "Signup.c"
#include "Signup.h"
#include "View.c"
#include "View.h"
#include "saveToFile.c"
#include "saveToFile.h"
#include "readFromFile.h"
#include "readFromFile.c"

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

    readUsers(&numberOfUsers, &users);
    readGoods(&numberOfGoods, &goods, numberOfUsers, users);
    readHistory(&buyerCartCount, &buyerCart, numberOfGoods, goods, numberOfUsers, users);

    while (TRUE)
    {
        // gettng input from user and checking for the entered command
        printf("\nEnter your Command:");
        char *input = getCommandLine();
        checkMalloc(input);
        command = strtok(input, " ");

        if (!strcmp(command, "signup") && loggedinUserId == -1)
        {
            doSignup(input, &numberOfUsers, &users);
            saveUsers(numberOfUsers, users);
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
            doView(input, users, loggedinUserId, buyerCart, buyerCartCount,
                   goods, numberOfGoods);
        }
        else if (!strcmp(command, "deposit") && loggedinUserId != -1 &&
                 !strcmp(users[loggedinUserId].userType, "buyer"))
        {
            doDeposit(input, &users, loggedinUserId);
            saveUsers(numberOfUsers, users);
        }
        else if (!strcmp(command, "add_goods") && loggedinUserId != -1 &&
                 !strcmp(users[loggedinUserId].userType, "seller"))
        {
            doAddGoods(input, users, loggedinUserId, &goods, &numberOfGoods);
            saveGoods(numberOfGoods, goods);
        }
        else if (!strcmp(command, "show_goods") && loggedinUserId != -1)
        {
            doShowGoods(input, goods, numberOfGoods, users);
        }
        else if (!strcmp(command, "buy") && loggedinUserId != -1 &&
                 !strcmp(users[loggedinUserId].userType, "buyer"))
        {
            doBuy(input, &goods, numberOfGoods, &users, loggedinUserId,
                  &buyerCart, &buyerCartCount);
            saveUsers(numberOfUsers, users);
            saveGoods(numberOfGoods, goods);
            saveHistory(buyerCartCount, buyerCart);
        }
        else
        {
            printf("Command Not Found!");
            free(input);
        }
    }

    // clearing all allocated memories
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
