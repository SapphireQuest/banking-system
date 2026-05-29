#ifndef BANK_H
#define BANK_H

void run_banking_system(void);
void create_account(void);
int create_account_number(void);

struct account
{
    int account_number;
    char name[100];
    char surname[100];
    char address[200];
    char identification_number[12];
    double balance;
};


#endif