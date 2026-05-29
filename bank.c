#include <stdio.h>
#include "bank.h"

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
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                printf("\n[ Feature coming soon! ]\n");
                break;
            case 0:
                printf("\nExiting system. Goodbye!\n");
                break;
            default:
                printf("\nError: Unknown option. Please try again.\n");
        }
    }
}