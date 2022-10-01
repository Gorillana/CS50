//Index Week 2 - Arrays
//Scrabble.c
//Readability.c
//Caesar.c

//Scrabble.c
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}

// Prototype
int compute_score(string word);

int main(void)
{
  // Get input words from both players
  string word1 = get_string("Player 1: ");
  string word2 = get_string("Player 2: ");
  // Score both words
  int score1 = compute_score(word1);
  int score2 = compute_score(word2);
  
  //TODO: Print the winner
  //If player one wins
  if (score1 > score2)
  {
    printf("Player 1 wins!\n");
  }
  
  // If player two wins
  else if (score2 > score1)
  {
    printf("Player 2 wins!\n");
  }
  
  // If there's a tie
  else
  {
    printf("Tie!\n");
  }
}

int compute_score(string word)
{
  // TODO: Compute and return score for string
  // Initialize score
  int score = 0;
  
  // Calculate score for word for upper and lower case
  for (int i = 0; i < strlen(word); i++)
    
    // Using POINT array to calc word score w ASCII value
    if (isupper(word[i]))
    {
      score += POINTS[word[i] - 65];
    }
  else if (islower(word[i]))
  {
    score += POINTS[word[i] - 97];
  }
  // Return score for string argument
  return score;
}

//Readability.c
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int cnt_words(string text);
int cnt_sentences(string text);

int main(void)
{
  // Get input from user
  string text = get_string("Text: ");
  
  // Link functions to main function via variables
  int letters = count_letters(text);
  int words = cnt_words(text):
  int sentences = cnt_sentences(text);
  
  // Output of Grade using Coleman-Liau formula and float conversion
  float L = letters / (float) words * 100;
  float S = sentences / (float) words * 100;
  
  int index = round(0.0588 * L - 0.296 * S - 15.8);
  
  // Determine grade level of text
  if (index < 1)
  {
    printf("Before Grade 1\n");
  }
  
  else if (index > 16)
  {
    printf("Grade 16+\n");
  }
  
  else
  {
    printf("Grade %i\n", index);
  }
}

int count_letters(string text)
{
  int letters = 0;
  
  for (int i = 0; i < strlen(text); i++)
  {
    // Counting letters with isalpha
    if (isalpha(text[i]))
    {
      letters++;
    }
  }
  return letters;
}

int cnt_words(string text)
{
  int words = 1;
  
  for (int i = 0; i < strlen(text); i++)
  {
    // Counting spaces to increment words
    if (text[i] == ' ')
    {
      words++;
    }
  }
  return words;
}

int cnt_sentences(string text)
{
  int sentences = 0;
  // Count sentences by checking for punctuation
  for (int i = 0; i < strlen(text); i++)
  {
    if (text[i] == '?' || text[i] == '!' || text[i] == '.')
    {
      sentences++;
    }
  }
  return sentences;
}

Caesar.c
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);

// Accept a single command-line argument

char rotate(char p, int k);

int main(int argc, string argv[])
{
  int k, len, i;
  
  // Program executes with 1 command-line arg & guarantees argv[1] is digit
  if (argc != 2 || !only_digits(argv[1]))
  {
    printf("Error - Correct Usage: ./caesar key \n");
    return 1;
  }
  
  // Convert argv[1] from a string to a digit
  k = atoi(argv[1]);
  
  // Output plaintext with two spaces without newline, prompt user
  string plaintext = get_string("Plaintext: ");
  len = strlen(plaintext);
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
  // Lowercase letters remain lowercase
  else if (islower(p))
  {
    c = (p - 'a' + k) % 26 + 'a';
  }
  // Non-alphabetical characters outputted unchanged
  else
  {
    c = p;
  }
  return c;
}
