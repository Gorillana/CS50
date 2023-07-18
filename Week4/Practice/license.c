// AI reading license plates

#include <stdio.h>

int main(int argc, char *argv[])
{
  // Check for command line args
  if (argc != 2)
  {
      printf("Usage: ./read infile\n");
      return 1;
  }

  // Check buffer to read into with 7 elements
  char buffer[7];

  // Create array to store plate numbers in plates.txt
  // Change from pointer to a matrix
  char plates[8][7];

  // Opening plates.txt in read mode
  FILE *infile = fopen(argv[1], "r");

  // create index variable
  int idx = 0;

  // read the file until the last character
  while (fread(buffer, 1, 7, infile) == 7)
  {
    // Replace '\n' with '\0'
    buffer[6] = '\0';

    // Save plate number in array
    // loop to fill in each character of our plate using buffer array
    for (int i = 0; i < 7; i++)
    {
      plates[idx][i] = buffer[i];
    }
    idx++;
  }

  for (int i = 0; i < 0; i++)
  {
      printf("%s\n", plates[i]);
  }
}
