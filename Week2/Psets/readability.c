// Calculate reading level
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
  int words = cnt_words(text);
  int sentences = cnt_sentences(text);

  // Output of Grade using Coleman-Liau formula and float conversion
  float L = letters / (float) words * 100;
  float S = sentences / (float) words * 100;

  int index = round (0.0588 * L - 0.296 * S - 15.8);

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
