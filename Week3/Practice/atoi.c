// Practice recursion

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i])
        {
            printf("Invalid input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // Gives how many elements there are so far
    int length = strlen(input);

    // base case, since 1 char left is the end of the string
    if (length == 1)
    {
        return input[0] - '0';
    }

    // the index of the last char in the string
    char last_char = input[length - 1];

    // convert this char into its numeric value
    int converted_last_digit = last_char - '0';

    // convert the last char into null character
    input[length - 1] = '\0';

    // Return this value plus 10 times the integer value of the new shortened string
    return converted_last_digit + 10 * convert(input);
}
