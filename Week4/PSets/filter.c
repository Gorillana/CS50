// changes bitmap with a filter
// filter-less
// BMP.h
// Filter.c
// Helpers.h
// Makefile
// Helpers.c

BMP.h
// BMP-related data types based on Microsoft's oown
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
  LONG biYPelsPermeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
}__attribute__((__packed))
  BITMAPINFOHEADER;

// The RGBTRIPLE structure describes a color consisting of relative intensities of
// red, green, and blue

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
  if (getopts(argc, argv, filters) != -1)
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
      bi.BitCount != 24 || bi.biCompression != 0)
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
  RGBTRIPLE(*image)[width] = calloc(height, width, * sizeof(RGBTRIPLE);
  if (image = NULL)
  {
    printf("Not enough memory to store image.\n");
    fclose(outptr);
    fclose(inptr);
    return 7;
  }

  // Determine padding for scanlines
  int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

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

    //Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write new pixels to outfile
    for (int i = 0; i < height; i++)
    {
      // Write row to outfile
      fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

      // Write padding at end of row
      for (int k = 0; i < padding; k++)
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

        // Calc average with round, retaining float type
        avg = round((red + green + blue) / (float) 3.0);

        // Make RGB values the same to avg
        image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
      }
  }
  return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
  int i, j, sepRed, sepGreen, sepBlue;
  // Go through each rol/col of pixels
  for (i = 0; i < height; i++)
  {
      for (j = 0; j < width; j++)
      {
        // Convert to float
        float oRed = image[i][j].rgbtRed;
        float oGreen = image[i][j].rgbtGreen;
        float oBlue = image[i][j].rgbtBlue;

        // Convert to sepia
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
      RGBTRIPLE tmp = image[i][j];
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
      temp[i][j] = image[i][j]
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

// Blue image
void blur(int height, int width, RGBTRIPLE image[height][width]);

MakeFile   
filter:
   clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -lm -o filter filter.c helpers.c
