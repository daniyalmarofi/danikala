#ifndef HEADERS_IMPORTED
#include "main.h"
#include "commonFunctions.h"
#endif

//** This Function gets the head and user data and adds a new node at the end of the list
void addUser(struct user *usersHead, char *username, char *password, int deposit, char *userType)
{
    // find the last node
    struct user *last = usersHead;
    while (last->next != NULL)
        last = last->next;

    // define the last
    struct user *newUser = (struct user *)malloc(sizeof(struct user));
    checkMalloc(newUser);
    newUser->username = username;
    newUser->password = password;
    newUser->deposit = deposit;
    newUser->userType = userType;
    newUser->next = NULL;

    // add new user at the end of the list
    last->next = newUser;
    return;
}

//** This Function gets the head and username and returns the pointer to that node
struct user *findUser(struct user *usersHead, char *username, char *userType)
{
    // find the last node
    struct user *current = usersHead->next;
    while (current != NULL)
    {
        if (!strcmp(current->username, username) && !strcmp(current->userType, userType))
            return current;
        current = current->next;
    }
    return NULL;
}