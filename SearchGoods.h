//** This Function does the search with 4 conditions
void doSearch(char *input, struct good *goodsHead);

//** this function does the search and shows the result
void searchAndShowResult(struct good *goodsHead, char *nameSearch, char *sellerUsernameSearch, int minPriceSearch, int maxPriceSearch);

//** This function searches for the goods with the input name
struct good *searchName(struct good *goodsHead, char *goodName);

//** This function searches for the goods from the sellerUsername
struct good *searchSellerUsername(struct good *goodsHead, char *sellerUsername);

//** This function searches for the goods with the min price
struct good *searchMinPrice(struct good *goodsHead, int minPrice, int searchedOnce);

//** This function searches for the goods with the max price
struct good *searchMaxPrice(struct good *goodsHead, int maxPrice, int searchedOnce);