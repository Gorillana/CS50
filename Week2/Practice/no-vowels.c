// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string replace(string input);

int main(int argc, string argv[])
{
  // Program accepts a single command-line arg
  if (argc != 2)
  {
    printf("Incorrect amount of command-line arguments\n");
    // If program executes with incorrect number of argc, return 1
    return 1;
  }
  string word = argv[1];

  // word relates to 'string input' in the function below
  string result = replace(word);

  // function prints converted word followed by \n
  printf("%s\n", result);
}

// Program contains function called replace and takes a string for input/output
string replace(string input)
{
    // links string input to word from main function
    string output = input;

    // loops through the entire word to make each letter of the user input be lowercase 
    for (int i = 0; i < strlen(input); i++)
    {
        char c = tolower(input[i]);

        // Uses switch statement to change vowels to numbers if they're in input
        switch(c)
        {
            case 'a': 
                output[i] = '6';
                break;
            
            case 'e':
                output[i] = '3';
                break;
            
            case 'i':
                output[i] = '1';
                break;
            
            case 'o':
                output[i] = '0';
                break;
            
            default:
                output[i] = input[i];
                break;
        }
    }
return output;
}


        
