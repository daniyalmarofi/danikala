#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** this function frees all the allocated memmories
void freeLinkedLists(struct user *usersHead, struct good *goodsHead, struct buyerCart *buyerCart)
{

    // loop on users to free
    struct user *theUser = usersHead->next;
    while (theUser != NULL)
    {
        // free uneeded memories
        struct user *temp = theUser->next;
        free(theUser->username);
        free(theUser->password);
        free(theUser->userType);
        free(theUser);
        theUser = temp;
    }
    free(usersHead);

    // loop on goods to free
    struct good *theGood = goodsHead->next;
    while (theGood != NULL)
    {
        // free uneeded memories
        struct good *temp = theGood->next;
        free(theGood->goodName);
        free(theGood);
        theGood = temp;
    }
    free(goodsHead);

    
    // loop on buyerCart to free
    struct buyerCart *cart = buyerCart->next;
    while (cart != NULL)
    {
        // free uneeded memories
        struct buyerCart *temp = cart->next;
        free(cart);
        cart = temp;
    }
    free(buyerCart);
}