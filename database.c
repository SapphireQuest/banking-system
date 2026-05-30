#include <stdio.h>
#include "database.h"
#include <string.h>

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

void display_sub_menu(void)
{
    int choice = -1;
    while (choice != 0)
    {        
        printf("\n--- Search Menu ---\n");
        printf("1. Search by account number\n");
        printf("2. Search by name\n");
        printf("3. Search by surname\n");
        printf("4. Search by address\n");
        printf("5. Search by identification number\n");
        printf("0. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice)
        {
            case 1:
                printf("\n--- Searching by account number ---\n");
                search_by_account_number();
                break;
            case 2:
                printf("\n--- Searching by name ---\n");
                search_by_string(choice);
                break;
            case 3:
                printf("\n--- Searching by surname ---\n");
                search_by_string(choice);
                break;
            case 4:
                printf("\n--- Searching by address ---\n");
                search_by_string(choice);
                break;
            case 5:
                printf("\n--- Searching by identification number ---\n");
                search_by_string(choice);
                break;
            case 0:
                printf("\nReturning to main menu...\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
    return;
}

void search_by_account_number(void)
{
    int account_number;
    struct account temp_account;

    printf("Enter account number to search: ");
    scanf("%d", &account_number);
    while (getchar() != '\n');

    FILE *file = find_account(account_number, &temp_account);
    if (file == NULL)
    {
        printf("\nError: Account not found.\n");
        return;
    }

    printf("\nAccount Number: %d\n", temp_account.account_number);
    printf("Name: %s\n", temp_account.name);
    printf("Surname: %s\n", temp_account.surname);
    printf("Address: %s\n", temp_account.address);
    printf("Identification Number: %s\n", temp_account.identification_number);
    printf("Balance: %.2f\n", temp_account.balance);
    fclose(file);
    return;
}

void search_by_string(int choice)
{
    char search_term[200];
    struct account temp_account;
    int found = 0;

    printf("Enter search term: ");
    scanf(" %199[^\n]", search_term);
    while (getchar() != '\n');

    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL)
    {
        printf("\nError: No accounts found.\n");
        return; 
    }

    while (fread(&temp_account, sizeof(struct account), 1, file) == 1) 
    {
        int match = 0;
        switch (choice)
        {
            case 2:
                match = (strcmp(temp_account.name, search_term) == 0);
                break;
            case 3:
                match = (strcmp(temp_account.surname, search_term) == 0);
                break;
            case 4:
                match = (strcmp(temp_account.address, search_term) == 0);
                break;
            case 5:
                match = (strcmp(temp_account.identification_number, search_term) == 0);
                break;
        }
        if (match)
        {
            printf("\nAccount Number: %d\n", temp_account.account_number);
            printf("Name: %s\n", temp_account.name);
            printf("Surname: %s\n", temp_account.surname);
            printf("Address: %s\n", temp_account.address);
            printf("Identification Number: %s\n", temp_account.identification_number);
            printf("Balance: %.2f\n", temp_account.balance);
            printf("-------------------------\n");
            found++;
        }
    }
    fclose(file);
    if (found > 0)
    {
        printf("\nTotal matches found: %d\n", found);
    }
    else
    {
        printf("\nNo matching accounts found.\n");
    }
}