// Index Week 4 - Memory
// Lab: Volume
// volume.c
// filter-less
  // bmp.h
  // filter.c
  // helpers.c
  // helpers.h
  // Makefile
// Recover.c

Volume.c
// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
  // Check command-line arguments
  if (argc != 4)
  {
    printf("Usage: ./volume input.wav output.wav factor \n");
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
  if (output == NULL)
  {
      printf("Could not open file.\n")
      return 1;
  }
  // Changes argv[3] to float in order to multiply the buffer
  float factor = atof(argv[3]);
  
  //TODO: Copy header from input file to output file
  uint8_t header[HEADER_SIZE];
  
  // Read header from input file
  fread(header, HEADER_SIZE, 1, input);
  
  // Write header to output file
  fwrite(header, HEADER_SIZE, 1, output);
  
  // TODO: Read samples from input file and write update data to output file
  int16_t buffer;
  
  // Loop through input file until eof
  while (fread(&buffer, sizeof(int16_t), 1, input))
  {
    // Multiply sample by volume factor
    buffer *= factor;
    
    // Write updated sample to output file
    fwrite(&buffer, sizeof(int16_t), 1, output);
  }
  
  // Close files
  fclose(input);
  fclose(output);
}

// filter-less
// BMP.h
// Filter.c
// Helpers.h
// Makefile
// Helpers.c

BMP.h
// BMP-related data types based on Microsoft's own
#include <stdint.h>

// These data types are essentially aliases for C/C++

typedef uint8_t BYTE;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef uint16_t WORD;

typedef struct
{
   WORD bfType;
   DWORD bfSize;
   WORD bfReserved1;
   WORD bfReserved2;
   DWORD bfOffbits;
}__attribute__((__packed))
  BITMAPFILEHEADER;

// The BITMAPINFOHEADER structure contains information about the
// dimensions and color format of a DIB [device-independent bitmap]

typedef struct
{
   DWORD biSize;
   LONG biWidth;
   LONG biHeight;
   WORD biPlanes;
   WORD biBitCount;
   DWORD biCompression;
   DWORD biSizeImage;
   LONG biXPelsPerMeter;
   LONG biYPelsPerMeter;
   DWORD biClrUsed;
   DWORD biClrImportant;
}__attribute__((__packed))
  BITMAPINFOHEADER;

// The RGBTRIPLE structure describes a color consisting of relative intesities of
// red, gree, and blue.

typedef struct
{
  BYTE rgbtBlue;
  BYTE rgbtGreen;
  BYTE rgbtRed;
}__attribute__((__packed))
  RGBTRIPLE;

Filter.c
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
  // Define allowable filters
  char *filters = "bgrs";
  
  // Get filter flag and check validity
  char filters = getopt(argc, argv, filters);
  if (filter == '?')
  {
    printf("Invalid filter.\n");
    return 1;
  }
  
  // Ensure only one filter
  if (getopt(argc, argv, filters) != -1)
  {
    printf("Only one filter allowed.\n");
    return 2;
  }
  
  // Ensure proper usage
  if (argc != optind + 2)
  {
    printf("Usage: ./filter [flag] infile outfile\n");
    return 3;
  }
  
  // Remember filenames
  char *infile = argv[optind];
  char *outfile = argv[optind + 1];
  
  // Open input file
  FILE *inptr = fopen(infile, "r");
  if (inptr == NULL)
  {
    printf("Could not open %s.\n", infile);
    return 4;
  }
  
  // Open output file
  FILE *outptr = fopen(outfile, "w");
  if (outptr == NULL)
  {
    fclose(inptr);
    printf("Could not create %s.\n", outfile);
    return 5;
  }
  
  // Read infile's BITMAPFILEHEADER
  BITMAPFILEHEADER bf;
  fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
  
  // Read infile's BITMAPINFOHEADER
  BITMAPINFOHEADER bi;
  fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
  
  // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
  if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
      bi.biBitCount != 24 || bi.biCompression != 0)
  {
    fclose(outptr);
    fclose(inptr);
    printf("Unsupported file format.\n");
    return 6;
  }
  
  // Get image's dimensions
  int height = abs(bi.biHeight);
  int width = bi.biWidth;
  
  // Allocate memory for image 
  RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE);
  if (image = NULL)
  {
    printf("Not enought memorty to store image.\n");
    fclose(outptr);
    fclose(inptr);
    return 7;
  }
                                    
  // Determine padding for scanlines
  int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4 ) % 4;

  // Iterate over infile's scanlines
  for (int i = 0; i < height; i++)
  {
    // Read row into pixel array 
    fread(image[i], sizeof(RGBTRIPLE), width, inptr);

    // Skip over padding 
    fseek(inptr, padding, SEEK_CUR);
  }
  
// Filter image
switch (filter)
      {
    // Blur
    case 'b':
        blur(height, width, image);
        break;

    // Grayscale
    case 'g':
        grayscale(height, width, image);
        break;

    // Reflection
    case 'r':
        reflect(height, width, image);
        break;

    // Sepia
    case 's':
        sepia(height, width, image);
        break;
      }
                                    
  // Write outfile's BITMAPFILEHEADER
  fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

  // Write outfile's BITMAPINFOHEADER
  fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

  // Write new pixels to outfile
  for (int i = 0; i < height; i++)
  {
   // Write row to outfile
    fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

    // Write padding at end of row
    for (int k = 0; k < padding; k++)
    {
        fputc(0x00, outptr);
    }
  }
                                    
    // Free memory for image
    free(image);

    // Close files
    fclose(inptr);
    fclose(outptr);
    return 0;
}                       

helpers.c
#include <stdio.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  int i, j, avg;
  float red, green, blue;

  // Loop over all pixels in image with nested for loop
  for (i = 0; i < height; i++)
  {
      for (j = 0; j < width; j++)
      {
        // Get RGB values 
        red = image[i][j].rgbtRed;
        green = image[i][j].rgbtGreen;
        blue = image[i][j].rgbtBlue;

        // Average
        avg = round((red + green + blue) / (float) 3.0);

        // Make RGB values gray be setting them to avg
        image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
      }
  }
  return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
  int i, j, sepRed, sepGreen, sepBlue;
  // Go through each row/col of pixels
  for (i = 0; i < height; i++)
  {
     for (j = 0; j < width; j++)
     {
       // Convert to float
       float oRed = image[i][j].rgbtRed;
       float oGreen = image[i][j].rgbtGreen;
       float oBlue = image[i][j].rgbtBlue;

       // convert to sepia
       sepRed = round(.393 * oRed + .769 * oGreen + .189 * oBlue);
       sepGreen = round(.349 * oRed + .686 * oGreen + .168 * oBlue);
       sepBlue = round(.272 * oRed + .534 * oGreen + .131 * oBlue);

       // limit sepia colors to max 255 value
       if (sepRed > 255)
       {
         sepRed = 255;
       }
       if (sepGreen > 255)
       {
         sepGreen = 255;
       }
       if (sepBlue > 255)
       {
         sepBlue = 255;
       }

       // update color values
       image[i][j].rgbtRed = sepRed;
       image[i][j].rgbtGreen = sepGreen;
       image[i][j].rgbtBlue = sepBlue;
     }
  }
  return;
}

// Reflect image horizontally
void reflect (int height, int width, RGBTRIPLE image[height][width])
{
  int i, j;
  // Go through each row and col of pic
  for (i = 0; i < height; i++)
  {
    for (j = 0; j < width / 2; j++)
    {
      // Adapt swap function to swap i and j in pics
      RBGTRIPLE tmp = image[i][j];
      image[i][j] = image[i][width - (j + 1)];
      image[i][width - (j + 1)] = tmp;
    }
  }
  return;
}
                                    
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
  int i, j, x, y, bRed, bBlue, bGreen, pixX, pixY;
  float counter;
  // Copy the image in a temp array
  RGBTRIPLE temp[height][width];
  for (i = 0; i < height; i++)
  {
    for (j = 0; j < width; j++)
    {
      temp[i][j] = image[i][j];
    }
  }

  for (i = 0; i < height; i++)
  {
    for(j = 0; j < width; j++)
    {
      bRed = bBlue = bGreen = 0;
      counter = 0.00;

      // adjacent pixels
      for (x = -1; x < 2; x++)
      { 
         for (y = -1; y < 2; y++)
         {
            pixX = i + x;
            pixY = j + y;

           // verify adjacent pixel
           if (pixX < 0 || pixX > (height - 1) || pixY < 0 || pixY > (width - 1))
           {
             continue;
           }
           // total image values
           bRed += image[pixX][pixY].rgbtRed;
           bGreen += image[pixX][pixY].rgbtGreen;
           bBlue += image[pixX][pixY].rgbtBlue;

           counter++;
         }

        // Average of adjacent pixels
        temp[i][j].rgbtRed = round(bRed / counter);
        temp[i][j].rgbtGreen = round(bGreen / counter);
        temp[i][j].rgbtBlue = round(bBlue / counter);
      }
    }
  }

// Copy back into original image
for (i = 0; i < height; i++)
 {
   for (j = 0; j < width; j++)
   {
       image[i][j].rgbtRed = temp[i][j].rgbtRed;
       image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
       image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
    }
  }
  return;
}                                   
                                  
helpers.h
#include "bmp.h"
                                    
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);
                                    
MakeFile   
filter:
   clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -lm -o filter filter.c helpers.c

                                    
Recover.c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// define/include unsigned int
typedef uint8_t BYTE;

int main(int argc, char * argv[])
{
  // Verify cmd line arg count is 2, if 1 is ret'd something went awry
  if (argc != 2)
  {
    printf("Usage: ./recover card.raw \n");
    return 1;
  }
  // Open a file in read mode
  FILE *input_file = fopen(argv[1], "r");

  // Check that the input_file is valid, if 2 is ret'd something went awry
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
      sprintf(filename, "%03i.jpg", made_imgs);

      // Open a file to write into by using write mode
      output_file = fopen(filename, "w");

      // Count number of images found
      made_imgs++;
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
