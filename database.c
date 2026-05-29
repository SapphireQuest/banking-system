#include <stdio.h>
#include "database.h"

int save_account_to_file(const struct account *account) 
{
    FILE *file = fopen("accounts.dat", "ab");
    if (file == NULL) 
    {
        return 0;
    }
    fwrite(&account, sizeof(struct account), 1, file);
    fclose(file);
    return 1;
}