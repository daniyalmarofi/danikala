//** This Function gets the head and goods data and adds a new node at the end of the list
void addGood(struct good *goodsHead, struct user *seller, char *goodName, int goodPrice, int goodCount, int status);

//** This Function gets the head and goodname and returns the pointer to that node
struct good *findGood(struct good *goodsHead, char *goodName);