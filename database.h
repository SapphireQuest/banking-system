#ifndef DATABASE_H
#define DATABASE_H
#include "bank.h"

int save_account_to_file(const struct account *account);
void display_all_accounts(void);
FILE *find_account(int search_id, struct account *target_account);
void display_sub_menu(void);
void search_by_account_number(void);
void search_by_string(int choice);
void take_out_car_insurance(void);
void save_insurance_to_file(struct car_insurance *insurance);
void display_user_insurances(int account_number);





#endif