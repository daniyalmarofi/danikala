//** This Function gets the head and user data and adds a new node at the end of the list
void addUser(struct user *usersHead, char *username, char *password, int deposit, char *userType);

//** This Function gets the head and username and returns the pointer to that node
struct user *findUser(struct user *usersHead, char *username);