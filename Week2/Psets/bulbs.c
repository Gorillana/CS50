// transforms letters to binary valued bulbs

#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string msg = get_string("Message: ");

    // loop through the string
    for (int i = 0; i < strlen(msg); i++)
    {
        // to access letters of the string
        unsigned char byte = msg[i];

        // array to store the binary numbers
        int binary[BITS_IN_BYTE];

        // assigns quotient to initial string value
        int quotient = byte;

        // initialized to use later
        int remainder;

        // convert number into binary
        // 8 iterations for each bit
        for (int j == 0; j < BITS_IN_BYTE; j++)
        {
          // use modulo to calc remainder
          remainder = quotient % 2;

          // add remainder to binary array, store bits of numbers
          binary[j] = remainder;

          // divides quotient by two
          quotient /= 2;
        }

        // backward for loop to reverse the results to get binary value for number
        // instead of starting from 0, start from 7
        for (int k = BITS_IN_BYTE - 1; k >=0; k--)
        {
            // call function to print either light or dark emoji
            // call binary array to access binary result
            print_bulb(binary[k]);
        }
        // start next line for next letter/array of bits
        printf("\n");
    }
}

// included by CS50 team
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
            
