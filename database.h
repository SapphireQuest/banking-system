#ifndef DATABASE_H
#define DATABASE_H
#include "bank.h"

int save_account_to_file(const struct account *account);
void display_all_accounts(void);
FILE *find_account(int search_id, struct account *target_account);



#endif