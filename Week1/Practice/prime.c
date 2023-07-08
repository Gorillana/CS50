// Prime numbers using recursion

#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
  // TODO
  // Exclude the base cases 1, 2, 3
  if (number == 2 || number == 3)
  {
      return true;
  }

  for(int i = 2; i < number; i++)
  {
      if(number % i == 0)
      { 
          return false;
      }
  }
return true;
}

