#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define HEADERS_IMPORTED
#define USERSFILE "users.txt"
#define GOODSFILE "goods.txt"
#define BUYHISTORYFILE "history.txt"
#define GOODACTIVE 'a'
#define GOODDELETED 'd'
#define BUYERNOTRATED 'n'
#define BUYERRATED 'r'

// defining structs
struct user
{
    char *username;
    char *password;
    char *userType;
    int deposit;
    struct user *next;
};

struct good
{
    struct user *seller;
    char *goodName;
    int goodPrice;
    int goodCount;
    int status;
    int numberOfRatings;
    int sumOfRates;
    struct good *next;
};

struct buyerCart
{
    struct user *buyer;
    struct good *boughtGood;
    int boughtPrice;
    int boughtCount;
    int rated;
    struct buyerCart *next;
};