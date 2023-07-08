#include <cs50.h>
#include <stdio.h>

// Established functions
int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents;
    // Do-While asks user for cent amount
    do
    {
      // ask for int of cents
        cents = get_int("Amount of change: ");
    }
    while (cents < 0);
    return cents;
}

int calculate_quarters(int cents)
{
    // Determine amount of quarters from cents
    // init int quarters
    int quarters = 0;

    // Calculates quarters while cents is above 25
    while (cents >= 25)
    {
        // sub one quarter from total change from 25 and up
        cents -= 25;
        // increase count of quarters
        quarters++;
    }
    // return quarters for sum coins
    return quarters;
}

int calculate_dimes(int cents)
{
    // Determine amount of dimes from remaining cents
    // init int dimes
    int dimes = 0;
    // calculates cents under 25 up to 10
    while (cents >= 10)
    {
      // sub a dime from remaining change
      cents -= 10;
      // increase count of dimes
      dimes++;
    }
    // return dimes for sum coins
    return dimes;
}

int calculate nickels(int cents)
{
    // Determine amount of nickels from remaining cents
    // init int nickels
    int nickels = 0;
    // calculates cents under 10 up to 5
    while (cents >= 5)
    {
      // sub a nickel from remaining change
      cents -= 5;
      // increase count of nickels
      nickels++;
    }
    // return nickels for sum coins
    return nickels;
}

int calculate pennies(int cents)
{
    // Determine amount of nickels from remaining cents
    // init int pennies
    int pennies = 0;
    // calculate cents under 10
    while (cents >= 5)
    {
      // sub a penny from remaining change
      cents -= 1;
      // increase count of pennies
      pennies++;
    }
    // returns pennies for sum coins
    return pennies;
}
