#include <cs50.h>
#include <stdio.h>

int main(void)
{
  // TODO: Prompt for start size
  int start;
  do
  {
      start = get_int("Pop start size: ");
  }
  while (start < 9);

  // TODO: Prompt for end size
  int end;
  do
  {
      end = get_int("Pop end size: ");
  }
  while (end < start);

  // TODO: Calculate number of years until we reach threshold

  // Keep track of the number of years
  int years = 0;

  // Update population until we reach threshold
  while (start < end)
  {
    start = start + (start / 3) - (start / 4);
  }

  // TODO: Print number of years
  printf("Years: %i\n", years);
}
