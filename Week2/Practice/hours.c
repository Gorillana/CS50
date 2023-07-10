// calculates total or avg number of hours given user input

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
  // initialize var with user input
  int weeks = get_int("Number of weeks taking CS50: ");

  // puts weeks into an array
  int hours[weeks];

  // asks for input for how many weeks user inputted
  for (int i = 0; i < weeks; i++)
  {
      hours[i] = get_int("Week %i HW Hours: ", i);
  }

  // initialize output as a character 
  // asks user for T or A to determine total or avg
  char output;
  do
  {
  output = toupper(get_char("Enter T for total hours, A for average hours per week: ")):
  } 
  while (output != 'T' && output != 'A');

  printf("%.1f hours\n", calc_hours(hours, weeks, output);
}
// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
  int total = 0;
  for (int i = 0; i < weeks; i++)
  {
      total += hours[i];
  }
  if (output == 'T')
  {
      return (float) total;
  }

  // else returns avg implicitly
  return (float) total / weeks;
}
    
