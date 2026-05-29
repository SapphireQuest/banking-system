#include <stdio.h>
#include <string.h>
#include "bank.h"
#include "database.h"

void run_banking_system(void) 
{
    int choice = -1;

    while (choice != 0) 
    {
        printf("\n=== BANKING SYSTEM MENU ===\n");
        printf("1. Create a new account\n");
        printf("2. List all accounts\n");
        printf("3. Search for an account\n");
        printf("4. Make a deposit\n");
        printf("5. Make a withdrawal\n");
        printf("6. Make a money transfer\n");
        printf("7. Take out car insurance\n");
        printf("0. Exit\n");
        printf("Select an option: ");

        if (scanf("%d", &choice) != 1) 
        {
            printf("\nError: Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (choice) 
        {
            case 1:
                printf("\n--- Creating a new account ---\n");
                create_account();
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                break;
            case 0:
                printf("\nExiting system. Goodbye!\n");
                break;
            default:
                printf("\nError: Unknown option. Please try again.\n");
        }
    }
}

void create_account(void) 
{
    struct account new_account;
    new_account.account_number = create_account_number();
    printf("Enter name: ");
    scanf("%99s", new_account.name);
    while (getchar() != '\n'); 
    printf("Enter surname: ");
    scanf("%99s", new_account.surname);
    while (getchar() != '\n'); 
    printf("Enter address: ");
    scanf(" %199[^\n]", new_account.address);
    while (getchar() != '\n');
    validate_identification_number(new_account.identification_number);
    new_account.balance = 0.0;

    int result = save_account_to_file(&new_account);
    if (result) 
    {
        printf("\nAccount created successfully! Account number: %d\n", new_account.account_number);
    } 
    else 
    {
        printf("\nError: Failed to save account. Please try again.\n");
    }
}

int create_account_number(void) 
{
    FILE *file = fopen("accounts.dat", "rb");
    if(file == NULL) 
    {
        return 1000;
    }
    int highest_account_number = 1000;
    struct account temp_account;
    while (fread(&temp_account, sizeof(struct account), 1, file) == 1) 
    {
        if (temp_account.account_number > highest_account_number) 
        {
            highest_account_number = temp_account.account_number;
        }
    }
    fclose(file);
    return highest_account_number + 1;
}

void validate_identification_number(char *identification_number) 
{
    int valid = 0;
    while (valid == 0) 
    {
        printf("Enter identification number (11 digits): ");
        scanf("%11s", identification_number);
        while (getchar() != '\n');

        if (strlen(identification_number) == 11) 
        {
            valid = 1;
        }
        else 
        {
            printf("\nError: Identification number must be exactly 11 digits.\n");
        }
    }
}