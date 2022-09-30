// index
// Hello.c
// Mario.c
// Cash.c


//Hello.c

#include <stdio.h>
#include <cs50.h>

int main(void)
{
	// Take name from user and says hello
	string name = get_string("What's your name? ");
	printf("Hello, %s\n", name);
}

//Mario.c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
	// Get input for varible from user
	int g;
	do
	{
		g = get_int("Width: ");
	}
	// Keep asking until user puts desired value
	while (g < 1 || g > 8);
	
	// For each row (initialize, conditional, increment)
	for (int row = 0; row < g; row++)
	{
		// Prints a space for every brick
		for (int space = 0; space < g-row; space++)
		{
			printf(" ");
		}
		// For each column init, cond, inc and print hash
		for (int col = 0; col <= row; col++)
		{
			printf("#");
		}
		// new line
		printf("\n");
	}
}
 
// Cash.c
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
	int coints = quarters + dimes + nickels + pennies;
	
	//Print total number of coins to give the customer 
	printf("%i\n", coins);
}

int get_cents(void)
{
	int cents;
	// Do-While aks the user for cent amount
	do
	{ 
		// Ask for int of cents
		cents = get_int("Amount of change: ");
	}
	while (cents < 0);
	return cents;
}

int calculate_quarters(int cents)
{
	// Determine amt of quarters from cents
	
	// Initalize int quarters
	int quarters = 0;
	while (cents >= 25)
	{
		// Subtract one quarter from total change from 25 and up
		cents -= 25;
		// Increase count of quarters
		quarters++;
	}
	// Returns quarters for sum coins
	return quarters;
}

int calculate_dimes(int cents)
{
	// Determine amount of dimes from remaining cents
	// Initialize int dimes
	int dimes = 0;
	// Calculate cents under 25
	while (cents >= 10)
	{
		// Subtract a dime from remaining change
		cents -= 10;
		// Increase count of dimes
		dimes++;
	}
		// Returns dimes for sum coins
		returns dimes;
}

int calculate_nickels(int cents)
{
	// Determine amount of nickels from remaining cents
	// Initialize int nickels
	int nickels = 0;
	// Calculate cents under 10
	while (cents >= 5)
	{
		// Subtract a nickel from remaining change
		cents -= 5;
		// Increase count of nickels
		nickels++;
	}
	// Returns nickels for sum coins
	return nickels;
}

int calculate_pennies(int cents)
{
	// Determine amount of pennies from remaining cents
	// Initialize int pennies
	int pennies = 0;
	// Calculates cents under 5
	while (cents >= 1)
	{
		cents -= 1;
		pennies++;
	}
	// Returns pennies for sum coins
	return pennies;
}
