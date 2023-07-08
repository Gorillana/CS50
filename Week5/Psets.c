
//Week 5
// Inheritance
// inheritance.c
// Speller
// dictionary.c
// dictionary.h
// Makefile
// speller.c

inheritance.c
//Simulate genetic inheritance of blood type
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parent alleles
typedef struct person
{
  struct person *parents[2];
  char alleles[2];
}
person;

const int GENERATION = 3;
const int INDENT_LENTH = 4;

person * create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
  // Seed random number generator
  srand(time(0));
  
  // Create a new family with three generations
  person *p = create_family(GENERATIONS);
  
  // Print family tree of blood types
  print_family(p, 0);
  
  // Free memory
  free_family(p);
}

// Create a new individual with 'generations'
person *create_family(int generations)
{
  // TODO: Allocate memory for new person
  person *p = malloc(sizeof(person));
  
  // If there are still generations left to create
  if (generations > 1)
  {
    // Create two new parents for current person by recursively calling create_family
    person *parent0 = create_family(generations - 1); 
    person *parent1 = create_family(generations - 1);
    
    // TODO: Set parent pointers for current person
    p->parents[0] = parent0;
    p->parents[1] = parent1;
    
    // TODO: Randomly assign current person's alleles based on the alleles of their parents
    p->alleles[0] = p->parents[0]->alleles[rand() % 2];
    p->alleles[1] = p->parents[1]->alleles[rand() % 2];
  }
  
  // If there are no generations left to create
  else
  {
    // TODO: Set parent pointers to NULL
    p->parents[0] = NULL;
    p->parents[1] = NULL;
    
    // TODO: Randomly assign alleles
    p->alleles[0] = random_allele();
    p->alleles[1] = random_allele();
  }
  
  // TODO: Return newly created person
  return p;
}

// Free 'p' and all ancestors of 'p'.
void free_familoy(person *p)
{
  // TODO: Handle base case
  if (p == NULL)
  {
    return;
  }
  
  // TODO: Free parents recursively
  free_family(p->parents[0]);
  free_family(p->parents[1]);
  
  // TODO: Free child
  free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
  // Handle base case
  if (p == NULL)
  {
    return;
  }
  
  // Print indentation
  for (int i = 0; i < generation * INDENT_LENGTH; i++)
  {
    printf(" ");
  }
  
  // Print person
  if (generation == 0)
  {
    printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1];
  }
  else if (generation == 1)
  { 
    printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
  }
  else
  { 
      for (int i = 0; i < generation - 2; i++_
      {
        printf("Great-");
      }
      printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
      }
  }
  // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele
char random_allele()
 {
   int r = rand() % 3;
   if (r == 0)
   {
     return 'A';
   }
   else if (r == 1)
   {
     return 'B';
   } 
   else
   {
     return 'O';
   }
 }

Speller.c
// Implements a spell checker
#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

// Undefine any definitions
#undef calculate
#undef getrusage

// Default dictionary
#define DICTIONARY "dictionaries/large"

// Prototype
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Check for correct number of args
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

// Structures for timing data
struct rusage before, after;

// Benchmarks
double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

// Determine dictionary to use
char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

// Load dictionary
getrusage(RUSAGE_SELF, &before);
bool loaded = load(dictionary);
getrusage(RUSAGE_SELF, &after);
  
// Exit if dictionary not loaded
if(!loaded)
{
    printf("Could not load %s.\n", dictionary);
    return 1;
}

// Calculate time to load dictionary
time_load = calculate(&before, &after);

// Try to open text
char *text = (argc == 3) ? argv[2] : argv[1];
FILE *file = fopen(text, "r");
if (file == NULL)
{
    printf("Could not open %s.\n", text);
    unload();
    return 1;
}
  
// Prepare to report misspellings
printf("\nMISSPELLED WORDS\n\n");

// Prepare to spell-check
int index = 0, misspellings = 0, words = 0;
char word[LENGTH + 1];

// Spell-check each word in text
char c;
while (fread(&c, sizeof(char), 1, file))
{
    // Allow only alphabetical characters and apostrophes
    if (isalpha(c) || (c == '\'' && index > 0))
    {
        // Append character to word
        word[index] = c;
        index++;
      
        // Ignore alphabetical strings too long to be words
        if (index > LENGTH)
        {
            // Consume remainder of alphabetical string
            while (fread(&c, sizeof(char), 1, file) && isalpha(c));
            
            // Prepare for new word
            index = 0;
        }
    }
  
  // Ignore words with numbers (like MS Word can)
  else if (isdigit(c))
  {
    // Consume remainder of alphanumeric string
    while (fread(&c, sizeof(char), 1, file) && isalnum(c));
    
    // Prepare for new word
    index = 0;
  }

  // We must have found a whole word
  else if (index > 0)
  {
      // Terminate current word
      word[index] = '/0';
    
      // Update counter
      words++;
    
      // Check word's spelling
      getrusage(RUSAGE_SELF, &before);
      bool misspelled = !check(word);
      getrusage(RUSAGE_SELF, &after);
    
      // Update benchmark
      time_check += calculate(&before, &after);
    
      // Print word if misspelled
      if (misspelled)
      {
        prinf("%s\n", word);
        misspellings++;
      }
    
      // Prepare for next word
      index = 0;
  }
}
  
  // Check whether there was an error
  if (ferror(file))
  {
      fclose(file);
      printf("Error reading %s.\n", text);
      unload();
      return 1;
  }
  
  // Close text
  fclose(file);
  
  // Determine dictionary's size
  getrusage(RUSAGE_SELF, &before);
  unsigned int n = size();
  getrusage(RUSAGE_SELF, &after);
  
  // Calculate time to determine dictionary's size
  time_size = calculate(&before, &after);

  // Unload dictionary
  getrusage(RUSAGE_SELF, &before);
  bool unloaded = unload();
  getrusage(RUSAGE_SELF, &after);
  
  // Abort if dictionary not unloaded
  if (!unloaded)
  {
    printf("Could not unload %s.\n", dictionary);
    return 1;
  }
  
  // Calculate time to unload dictionary
  time_unload = calculate(&before, &after);
  
  // Report benchmarks
  printf("\nWORDS MISSPELLED:  %\n", misspellings);
  printf("WORDS IN DICTIONARY: %d\n", n);
  printf("WORDS IN TEXT:       %d\n", words);
  printf("TIME IN load:        %.2f\n", time_load);
  printf("TIME IN check:       %.2f\n", time_check);
  printf("TIME IN size:        %.2f\n", time_size); 
  printf("TIME IN unload:      %.2f\n", time_unload);
  printf("TIME IN TOTAL:       %.2f\n\n", 
         time_load + time_check + time_size + time_unload);
  
  // Success
  return 0;
}

// Returns number of seconds between b and a
double calculate(const struc rusage *b, const struct rusage *a)
{
 if (b == NULL || a == NULL)
 {
   return 0.0;
 }
 else
 {
    return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
              (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
             ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
              (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
            / 1000000.0);
 }
}

Dictionary.c
// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
 char word[LENGTH + 1];
 struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// For aca text, N = 26 - 30 second result; with N = 1000, down to 1.86, 100000, 1.36
// Given diminishing returns, left N at 1000
const unsigned int N = 1000;

// Hash table
node *table[N];

// Declare variables
unsigned int count = 0;
unsigned int hash_val = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
 // Open dictionary
 FILE *txt = fopen(dictionary, "r");

 // Return NULL if file cannot be opened
 if (dictionary == NULL)
 {
   printf("Unable to open %s\n", dictionary);
   return false;
 }
 // Declare variable called text
 char text[LENGTH + 1];

 // Scan dictionary for strings up until EOF
 while (fscanf(txt, "%s", text) != EOF)
 {
      // Allocate memory for new node
      node *n = malloc(sizeof(node));

     // If malloc returns NULL, return false
     if (n == NULL)
     {
        return false;
     }

     // Copy word into node
     strcpy(n->word, text);
     hash_val = hash(text);
     n->next = table[hash_val];
     table[hash_val] = n;
     count++;
   }
 fclose(txt);
 return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
 {
   // TODO: Improve this has function
   // Researched from Anveat on YT and JR on Medium
   // but saw the basic format in the cs50 hash table short with Doug :)
   unsigned long calc = 0;
   for (int = 0; i < strlen(word); i++)
   {
        calc += tolower(word[i]);
   }
   return calc % N;
 }

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
 {
   // Return size of dictionary
   return count;
 }

// Return true if word is in dictionary, else false
bool check(const char *word)
 {
   // TODO:
   hash_val = hash(word);
   node *cursor = table[hash_val];

   // Traverse through linked list comparing despite case
   while (cursor != NULL)
   {
     if (strcasecmp(word, cursor->word) == 0)
     {
        return true;
     }
     cursor = cursor->next;
   }
   return false;
 }

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
 {
   // Iterate through buckets
   for (int i = 0; i < N; i++)
   {
     // Set cursor to the start of the linked list
     node *cursor = table[i];

     // If cursor is not NULL, free memory
     while (cursor != NULL)
     {
       // Create tmp
       node *tmp = cursor;

       // Move cursor to next node
       cursor = cursor -> next;

       // Free up tmp
       free(tmp);
     }
     //If cursor is NULL and i is at the end of the hash table
     if (cursor == NULL && i == N - 1)
     {
       return true;
     }
   }
   return false;
 }

Dictionary.h
// Declares a dictionary's functionality
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H

Makefile
speller:
     clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o speller.o speller.c
    clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o dictionary.o dictionary.c
    clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o speller speller.o dictionary.o -lm
