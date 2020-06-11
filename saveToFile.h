//** This Function saves the users array to defined USERSFILE .txt file
void saveUsers(int numberOfUsers, struct user *users);

//** This Function saves the goods array to defined GOODSFILE .txt file
void saveGoods(int numberOfGoods, struct good *goods);

//** This Function saves the buyerCart array to defined BUYHISTORYFILE .txt file
void saveHistory(int buyerCartCount, struct buyerCart *buyerCart);