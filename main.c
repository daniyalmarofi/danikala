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
#include "RemoveGoods.c"
#include "RemoveGoods.h"
#include "ChangeGoodsPrice.c"
#include "ChangeGoodsPrice.h"
#include "RateGoods.c"
#include "RateGoods.h"
#include "SearchGoods.c"



#include "usersLinkedList.c"
#include "usersLinkedList.h"
// #include "goodsLinkedList.c"
// #include "goodsLinkedList.h"


int main()
{
    printf("Welcome To DaniKala!");

    struct user *usersHead = (struct user *)malloc(sizeof(struct user));
    usersHead->next = NULL;

    addUser(usersHead, "dani", "pass", 0, "seller");
    addUser(usersHead, "dani", "pass", 1000, "buyer");

    struct good *goodsHead = (struct good *)malloc(sizeof(struct good));
    goodsHead->next = NULL;

    addGood(goodsHead, usersHead->next, "watch2", 1000, 10, GOOD_ACTIVE);
    addGood(goodsHead, usersHead->next, "watch", 1000, 10, GOOD_ACTIVE);

    char *command;
    struct user *loggedinUser = usersHead->next;

    struct buyerCart *buyerCart = (struct buyerCart *)malloc(sizeof(struct buyerCart));
    buyerCart->next = NULL;

    while (TRUE)
    {
        // gettng input from user and checking for the entered command
        printf("\nEnter your Command:");
        char *input = getCommandLine();
        checkMalloc(input);
        command = strtok(input, " ");

        if (!strcmp(command, "signup") && loggedinUser == NULL)
        {
            doSignup(input, usersHead);
        }
        else if (!strcmp(command, "login") && loggedinUser == NULL)
        {
            doLogin(input, usersHead, &loggedinUser);
        }
        else if (!strcmp(command, "logout") && loggedinUser != NULL)
        {
            doLogout(input, &loggedinUser);
        }
        else if (!strcmp(command, "view") && loggedinUser != NULL)
        {
            doView(input, loggedinUser, buyerCart, goodsHead);
        }
        else if (!strcmp(command, "deposit") && loggedinUser != NULL && !strcmp(loggedinUser->userType, "buyer"))
        {
            doDeposit(input, loggedinUser);
        }
        else if (!strcmp(command, "add_goods") && loggedinUser != NULL && !strcmp(loggedinUser->userType, "seller"))
        {
            doAddGoods(input, loggedinUser, goodsHead);
        }
        else if (!strcmp(command, "show_goods") && loggedinUser != NULL)
        {
            doShowGoods(input, goodsHead);
        }
        else if (!strcmp(command, "buy") && loggedinUser != NULL && !strcmp(loggedinUser->userType, "buyer"))
        {
            doBuy(input, goodsHead, loggedinUser, buyerCart);
        }
        else if (!strcmp(command, "remove_goods") && loggedinUser != NULL && !strcmp(loggedinUser->userType, "seller"))
        {
            doRemoveGoods(input, loggedinUser, goodsHead);
        }
        else if (!strcmp(command, "change_goods_price") && loggedinUser != NULL && !strcmp(loggedinUser->userType, "seller"))
        {
            doChangeGoodsPrice(input, loggedinUser, goodsHead);
        }
        else if (!strcmp(command, "rate_goods") && loggedinUser != NULL && !strcmp(loggedinUser->userType, "buyer"))
        {
            doRateGoods(input, goodsHead, loggedinUser, buyerCart);
        }
        else if(!strcmp(command, "search") && loggedinUser != NULL){
            doSearch(input, goodsHead);
        }
        else
        {
            printf("Command Not Found!");
            free(input);
        }
    }

    return 0;
}
