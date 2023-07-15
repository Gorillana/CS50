// takes two words and figures out which one is worth more points
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

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

  // TODO: Print the winner
  // If player one wins
  if (score1 > score2)
  {
      printf("Player 1 wins!\n");
  }
  // If player two wins
  else if (score2 > score1)
  {
      printf("Player 2 wins!\n");
  }
  // if there's a tie
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

  // Calculate score for word for upper and lower case letters
  for (int i = 0; i < strlen(word); i++)

      // Using POINT array to calc word score w ASCII val
      if (isupper(word[i]))
      {
          // gives an index value based on POINTS array
          score += POINTS[word[i] - 'A'];
      }
      // Using POINT array to calc word score w ASCII val
      else if (islower(word[i]))
      {
          // gives an index value based on POINTS array
          score += POINTS[word[i] - 'a'];
      }
  // REturn score for string argument
  return score;
}
    
