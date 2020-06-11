//** this function gets a line from the file specified by FILE *fp
char *getFileLine(FILE *fp);

//** This Function reads the users array from defined USERSFILE .txt file
void readUsers(int *numberOfUsers, struct user **users);

//** This Function reads the goods array from defined GOODSFILE .txt file
void readGoods(int *numberOfGoods, struct good **goods);