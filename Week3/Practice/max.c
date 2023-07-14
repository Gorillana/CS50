// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
  int n;
  do
  {
      n = get_int("Number of elements: ");
  }
  while (n < 1);

  int arr[n];

  // asks user for each element
  for (int i = 0; i < n; i++)
  {
      arr[i] = get_int("Element %i: ", i);
  }

  printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    // uses variable to keep track of max value by using first element of the array
    int max_val = array[0];

    // loop through array
    for (int i = 0; i < n; i++)
    {
      // swaps highest value to variable
      if (max_val < array[i])
        {
            max_val = array[i];
        }
    }

return max_val;
}
