// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool ckLower = false;
    bool ckUpper = false;
    bool ckNumber = false;
    bool ckSymbol = false;

    for (int i = 0; i < strlen(password); i++)
    {
        if (islower(password[i]))
        {
            ckLower = true;
        }
        if (isupper(password[i]))
        {
            ckUpper = true;
        }
        if (isdigit(password[i]))
        {
            ckNumber = true;
        }
        if (!isalnum(password[i]))
        {
            ckSymbol = true;
        }
    }

    if (ckLower == true && ckUpper == true && ckNumber == true && ckSymbol == true)
    {
        return true;
    }
    return false;
}
