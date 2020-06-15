#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define HEADERS_IMPORTED
#define USERS_FILE "users.txt"
#define GOODS_FILE "goods.txt"
#define BUY_HISTORY_FILE "history.txt"
#define GOOD_ACTIVE 'a'
#define GOOD_DISABLE 'd'
#define GOOD_DELETED 'd'
#define BUYER_NOT_RATED 'n'
#define BUYER_RATED 'r'

#define MIN_DISABLE_NUMBER_OF_RATES 1
#define MIN_ACTIVE_RATE 2

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