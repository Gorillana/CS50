#include <cs50.h>
#include <stdio.h>

int main(void)
{
  // get input for variable from user
  int g;
  do
  {
      g = get_int("Width: ");
  }
  // keeps asking until user puts value btw 1 and 8
  while (g < 1 || g > 8);

// for each row(init, cond, inc)
  for (int r = 1; r <= g; r++)
  {
      // prints a space for every brick
      for (int s = 1; s <= g - r; s++)
      {
          printf(" ");
      }
      // for each col(init, cond, inc)
      for (int c = 1; c <= r; c++)
      {
          // Print hash;
            printf("#");
      }
      // new line
      printf("\n");
  }
}

