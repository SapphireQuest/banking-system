#include <stdio.h>
#include "database.h"

int save_account_to_file(const struct account *account) 
{
    FILE *file = fopen("accounts.dat", "ab");
    if (file == NULL) 
    {
        return 0;
    }
    fwrite(account, sizeof(struct account), 1, file);
    fclose(file);
    return 1;
}

void display_all_accounts(void)
{
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL)
    {
        printf("Error: No accounts found.\n");
        return; 
    }
    struct account temp_account;
    while (fread(&temp_account, sizeof(struct account), 1, file) == 1) 
    {
        printf("Account Number: %d\n", temp_account.account_number);
        printf("Name: %s\n", temp_account.name);
        printf("Surname: %s\n", temp_account.surname);
        printf("Address: %s\n", temp_account.address);
        printf("Identification Number: %s\n", temp_account.identification_number);
        printf("Balance: %.2f\n", temp_account.balance);
        printf("-------------------------\n");
    }
    fclose(file);
}

FILE* find_account(int search_id, struct account *target_account) 
{
    FILE *file = fopen("accounts.dat", "r+b");
    if (file == NULL) 
    {
        return NULL; 
    }

    while (fread(target_account, sizeof(struct account), 1, file) == 1) 
    {
        if (target_account->account_number == search_id) 
        {
            return file; 
        }
    }
    fclose(file);
    return NULL;
}