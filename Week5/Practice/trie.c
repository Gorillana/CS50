// Saves popular dog names in a trie

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_ALPHABET 26
#define MAXCHAR 20

typedef struct node
{
  bool is_word;
  struct node *children[SIZE_OF_ALPHABET];
}
node;

// Function prototypes
bool check(char *word);
bool unload(void);
bool unloader(node *current);

// Root of trie
node *root;

// Buffer to read dog names into
char name[MAXCHAR];

int main(int argc, char *argv[])
{
    // check for command line args
    if (argc != 2)
    {
      printf("Usage: ./trie infile\n");
      return 1;
    }
  
    // File with names
    FILE *infile = fopen(argv[1], "r");
    if (!infile)
    {
      printf("Error opening file!\n");
      return 1;
    }
  
    // Allocate root of trie
    root = malloc(sizeof(node));
  
    if (root == NULL)
    {
      return 1;
    }
  
    root->is_word = false;
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        root->children[i] = NULL;
    }
  
    // Add words to the trie
    while (fscanf(infile, "%s", name) == 1)
    {
        node *cursor = root;
  
        // loop through all the letters of our name
        for (int i = 0, n = strlen(name); i < n; i++)
          {
              // subtract to make the index of the letters of the name be indexed 0 according to ascii
              int index = tolower(name[i]) - 'a';
              if (cursor->children[index] == NULL)
              {
                // Make node
                node *new = malloc(sizeof(node));
                new->is_word = false;
                for (int j = 0; j < SIZE_OF_ALPHABET; j++)
                {
                    new->children[j] = NULL;
                }
                cursor->children[index] = new;
              }
  
              // Go to node which we just made
              cursor = cursor->children[index];
        }
  
        // if we are at the end of the word, mark it as being a word
        cursor->is_word = true;
    }

    if (check(get_string("Check word: ")))
    {
        printf("Found!\n");
    }
    else
    {
      printf("Not found.\n");
    }

    if (!unload())
    {
      printf("Problem freeing memory!\n");
      return 1;
    }

    fclose(infile);
}

// TODO: Complete the check function, return true if found, false if not found
bool check(char* word)
{
    // node pointer cursor to the root of the trie
    node *cursor = root;

    // iterate through every letter in the argument word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
      // checking index of the current letter
      // case insensitive by using tolower for each letter
      int index = tolower(word[i]) - 'a';

      // to check if index is within 0 and 25
      if(index < 0 || index >= SIZE_OF_ALPHABET)
      {
        // word is not in alphabet
        return false;
      }

      // reached end of name stored in trie
      if (cursor->children[index] == NULL)
      {
          return false;
      }
      // continues to loop moving cursor through the trie
      cursor = cursor->children[index];
    }
  // is_word is true or false
  return cursor->is_word;
}

// Unload trie from memory
bool unload(void)
{
  // The recursive function handles all of the freeing
  unloader(root);

  return true;
}

void unloader(node* current)
{

    // Iterate over all the children to see if they point to anything and go there if so
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        if (current->childre[i] != NULL)
        {
            unloader(current->children[i]);
        }
    }

    // After we check all the children point to null we can get ride of the node
    // and return to the previous iteration of this function
    free(current);
}


















