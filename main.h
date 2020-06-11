#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define HEADERS_IMPORTED
#define USERSFILE "users.txt"

// defining structs
struct user
{
    char* username;
    char* password;
    char* userType;
    int deposit;
};

struct good
{
    int sellerId;
    char* goodName;
    int goodPrice;
    int goodCount;
};

struct buyerCart
{
    int buyerId;
    int goodId;
    int boughtCount;
};