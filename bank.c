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
                printf("\n--- Listing all accounts ---\n");
                display_all_accounts();
                break;
            case 3:
                printf("\n--- Searching for an account ---\n");
                display_sub_menu();
                break;
            case 4:
                deposit();
                break;
            case 5:
                withdraw();
                break;
            case 6:
                transfer();
                break;
            case 7:
                //take_out_car_insurance();
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

    char confirmation;
    printf("\nAre you sure you want to create this account? (y/n): ");
    scanf(" %c", &confirmation);
    while (getchar() != '\n');

    if (confirmation != 'y' && confirmation != 'Y') 
    {
        printf("\nAccount creation cancelled.\n");
        return;
    }

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

void deposit(void)
{
    int account_number;
    double amount;
    struct account temp_account;
    
    printf("Enter account number: ");
    scanf("%d", &account_number);
    while (getchar() != '\n');
    
    FILE *file = find_account(account_number, &temp_account);
    if (file == NULL)
    {
        printf("\nError: Account not found.\n");
        return;
    }

    printf("\nCurrent balance: %.2f\n", temp_account.balance);
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    while (getchar() != '\n');

    char confirmation;
    printf("\nAre you sure you want to deposit %.2f to account %d? (y/n): ", amount, account_number);
    scanf(" %c", &confirmation);
    while (getchar() != '\n');
    if (confirmation != 'y' && confirmation != 'Y') 
    {
        printf("\nDeposit cancelled.\n");
        fclose(file);
        return;
    }

    if (amount > 0) 
    {
        temp_account.balance += amount;
        fseek(file, -sizeof(struct account), SEEK_CUR);
        fwrite(&temp_account, sizeof(struct account), 1, file);
        fflush(file);

        printf("\nDeposit successful! New balance: %.2f\n", temp_account.balance);
    }
    else 
    {
        printf("\nError: Deposit amount must be positive.\n");
    }
    fclose(file);
    return;
}

void withdraw(void)
{
    int account_number;
    double amount;
    struct account temp_account;

    printf("Enter account number: ");
    scanf("%d", &account_number);
    while (getchar() != '\n');

    FILE *file = find_account(account_number, &temp_account);
    if (file == NULL)
    {
        printf("\nError: Account not found.\n");
        return;
    }

    printf("\nCurrent balance: %.2f\n", temp_account.balance);
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);
    while (getchar() != '\n');

    char confirmation;
    printf("\nAre you sure you want to withdraw %.2f from account %d? (y/n): ", amount, account_number);
    scanf(" %c", &confirmation);
    while (getchar() != '\n');
    if (confirmation != 'y' && confirmation != 'Y') 
    {
        printf("\nWithdrawal cancelled.\n");
        fclose(file);
        return;
    }

    if (amount > 0) 
    {
        if (temp_account.balance >= amount) 
        {
            temp_account.balance -= amount;
            fseek(file, -sizeof(struct account), SEEK_CUR);
            fwrite(&temp_account, sizeof(struct account), 1, file);
            fflush(file);

            printf("\nWithdrawal successful! New balance: %.2f\n", temp_account.balance);
        }
        else 
        {
            printf("\nError: Insufficient funds. Current balance: %.2f\n", temp_account.balance);
        }
    }
    else 
    {
        printf("\nError: Withdrawal amount must be positive.\n");
    }
    fclose(file);
    return;
}

void transfer(void)
{
    int from_account_number, to_account_number;
    double amount;
    struct account from_account, to_account;

    printf("Enter your account number: ");
    scanf("%d", &from_account_number);
    while (getchar() != '\n');
    
    FILE *from_file = find_account(from_account_number, &from_account);
    if (from_file == NULL)
    {
        printf("\nError: Your account not found.\n");
        return;
    }

    printf("Enter destination account number: ");
    scanf("%d", &to_account_number);
    while (getchar() != '\n');

    FILE *to_file = find_account(to_account_number, &to_account);
    if (to_file == NULL)
    {   
        printf("\nError: Destination account not found.\n");
        fclose(from_file);
        return;
    }
    if (from_account_number == to_account_number)
    {
        printf("\nError: Cannot transfer to the same account.\n");
        fclose(from_file);
        fclose(to_file);
        return;
    }

    printf("\nYour current balance: %.2f\n", from_account.balance);
    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);
    while (getchar() != '\n');

    if (amount > 0)
    {
        if (from_account.balance >= amount) 
        {
            char confirmation;
            printf("\nAre you sure you want to transfer %.2f from account %d to account %d? (y/n): ", amount, from_account_number, to_account_number);
            scanf(" %c", &confirmation);
            while (getchar() != '\n');
            if (confirmation != 'y' && confirmation != 'Y') 
            {
                printf("\nTransfer cancelled.\n");
                fclose(from_file);
                fclose(to_file);
                return;
            }

            from_account.balance -= amount;
            to_account.balance += amount;

            fseek(from_file, -sizeof(struct account), SEEK_CUR);
            fwrite(&from_account, sizeof(struct account), 1, from_file);
            fflush(from_file);

            fseek(to_file, -sizeof(struct account), SEEK_CUR);
            fwrite(&to_account, sizeof(struct account), 1, to_file);
            fflush(to_file);
            
            printf("\nTransfer successful! Your new balance: %.2f\n", from_account.balance);
        }
        else 
        {
            printf("\nError: Not enough funds. Your current balance: %.2f\n", from_account.balance);
        }
    }
    else 
    {
        printf("\nError: Transfer amount must be positive.\n");
    }
    fclose(from_file);
    fclose(to_file);
    return;
}
