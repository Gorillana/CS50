// execute a basic caesar cipher
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char p, int k);

int main(int argc, string argv[])
{
  // init 3 vars
  int k, len, i;

  // Program executes w 1 cmd-line arg & guarantee argv[1] is digit
  if (argc != 2 || !only_digits(argv[1]))
  {
      printf("Error - Correct Usage: .\caesar key \n");
      return 1;
  }

  // Convert argv[1] from a string to a digit
  k = atoi(argv[1]);

  // Output plaintext with two spaces without newline, prompt user
  string plaintext = get_string("Plaintext: ");

  len = strlen(plaintext)

  // +1 is necessary since the array needs to have space to store null
  char cipher[len + 1];
  for (i = 0; i < len; i++)
    {
      cipher[i] = rotate(plaintext[i], k);
    }
  cipher[i] = '\0';
  // Output ciphertext with one space without newline
  printf("Ciphertext: %s", cipher);
  printf("\n");
}

bool only_digits(string s)
{
  int len = strlen(s);
  for (int i = 0; i < len; i++)
    {
      if (!isdigit(s[i]))
      {
        return false;
      }
    }
  return true;
}

// Preserve case, alphabetical characters remain alphabetical
char rotate(char p, int k)
{
  char c;
  // Capitalized letters remain capitalized
  if (isupper(p))
  {
    c = (p - 'A' + k) % 26 + 'A';
  }
  // Lowercase remains lowercase
  else if (islower(p))
  {
    c = (p - 'a' + k) % 26 + 'a';
  }
  // Non-alphabetical characters outputted changed
  else
  {
    c = p;
  }

  return c;
}

