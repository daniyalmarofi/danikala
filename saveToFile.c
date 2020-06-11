#ifndef HEADERS_IMPORTED
#include "commonFunctions.h"
#include "main.h"
#endif

//** This Function saves the users array to defined USERSFILE .txt file
void saveUsers(int numberOfUsers, struct user* users) {
    FILE* fp;

    fp = fopen(USERSFILE, "w");

    // loop to users array and save each to file
    int i = 0;
    while (i < numberOfUsers && numberOfUsers > 0) {
        fprintf(fp, "%s, %s, %s, %d\n", users[i].username, users[i].password,
                users[i].userType, users[i].deposit);
        i++;
    }
    fclose(fp);
}