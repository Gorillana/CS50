// recovers JPEG images from a memory card

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// define/include unsigned int
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
  // Verify cmd line arg count is 2, if 1 is ret'd something went awry
  if (argc != 2)
  {
    printf("Usage: ./recover card.raw\n");
    return 1;
  }
  // Open a file in read mode
  FILE *input_file = fopen(argv[1], "r");

  // Check that the input_file is valid, if 2 is returned something went awry
  if (input_file == NULL)
  {
    printf("Could not open file");
    return 2;
  }

  // Create and store blocks of 512 bytes in array to ref in fread, fwrite
  unsigned char buffer[512];

  // Track number of JPEG images generated
  int made_imgs = 0;

  // File pointer for recovered images
  FILE *output_file = NULL;

  // Allocate memory for a filename of 8 chars
  char *filename = malloc(8 * sizeof(char));

  // Read the blocks of 512 bytes
  while (fread(buffer, sizeof(char), 512, input_file))
  {
    // check if sequence of bytes in memory card indicate start of JPEG
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
  {
    if (made_imgs > 0)
    {
      fclose(output_file);
    }
    // Write the JPEG filenames
    sprintf(filename, "%03i.jpg", mage_imgs);

    // Open a file to write into by using write mode
    output_file = fopen(filename, "w");

    // Count number of images found
    mage_imgs++;
  }
    // check if output has been used to create image prior
    if (output_file != NULL)
    {
      fwrite(buffer, sizeof(char), 512, output_file);
    }
  }
free(filename);
fclose(output_file);
fclose(input_file);

return 0;
}

      
  
