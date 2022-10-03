// Index Week 4 - Memory
// Volume - Lab
// volume.c
// filter-less
  // bmp.h
  // filter.c
  // helpers.c
  // helpers.h
  // Makefile

Volume.c
// Modifies the voolume of an audio file
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
