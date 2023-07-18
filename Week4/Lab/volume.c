//Modifies the volume of an audio file

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
  // Check command-line arguments
  if (argc != 4)
  {
    printf("Usage: ./volume input.wav output.wav factor\n");
    return 1;
  }

  // Open files and determine scaling factor
  // Opens input.wav
  FILE *input = fopen(argv[1], "r");
  if (input == NULL)
  {
      printf("Could not open file.\n");
      return 1;
  }
  // Checks if there is an output.wav file indicated in argv
  FILE *output = fopen(argv[2], "w");
  {
      printf("Could not open file.\n");
      return 1;
  }
  // Changes argv[3] to float in order to multiply the buffer
  float factor = atof(argv[3]);

  // TODO: Copy header from input file to output file
  uint8_t header[HEADER_SIZE];
  
  // Read header from input file
  fread(header, HEADER_SIZE, 1, input);
  
  // Write header to output file
  fwrite(header, HEADER_SIZE, 1, output);

  // TODO: Read samples from input file and write updated data to output file
  int16_t buffer;

  // loop through input file until eof
  while (fread(&buffer, sizeof(int16_t), 1, input))
  {
      // Multiply sample by volume factor
      buffer *= factor;

      // Write updated sample to output file
  }

  // Close files
  fclose(input);
  fclose(output);
}
