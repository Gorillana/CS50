// Index Week 3 - Algorithms
// Sort not included as it's an exercise
// Plurality.c
// Runoff.c

Plurality.c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
  string name;
  int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
  // Check for invalid usage
  if (argc < 2)
  {
    printf("Usage: plurality [candidate ...]\n");
    return 1;
  }
  
  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX)
  {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }
  
  for (int i = 0; i < candidate_count; i++)
  {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
  }
  
  int voter_count = get_int("Number of voters: ");
  
  // Loop over all voters
  for (int i = 0; i < voter_count; i++)
  {
    string name = get_string("Vote: ");
    
    // Check for invalid vote
    if (!vote(name))
    {
      printf("Invalid vote.\n");
    }
  }
  // Display winner of election
  print_winner();
}

//Update vote totals given a new vote
bool vote(string name)
{
  for (int i = 0; i < candidate_count; i++)
       {
         // When someone gets a vote, add to their tally
         if (strcmp(candidates[i].name, name) == 0)
         {
           candidates[i].votes++;
           return true;
         }
       }
       return false;
}

// Print the winner (or winners of the election
void print_winner(void)
{
  int topcand = 0;
  for (int i = 0; i < candidate_count; i++)
  {
    // Figure out who has the most votes
    if (candidates[i].votes > topcand)
    {
      topcand = candidates[i].votes;
    }
  }
  
  for (int i = 0; i < candidate_count; i++)
  {
    // Print whoever has the most votes
    if (candidates[i].votes == topcand)
    {
      printf("%s\n", candidates[i].name);
    }
  }
 return;
}

Runoff.c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences [i][j] is the jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
  string name;
  int votes;
  bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
  // Check for invalid usage
  if (argc < 2)
  {
    printf("Usage: runoff [candidate ...]\n");
    return 1;
  }
  
  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX_CANDIDATES)
  {
    printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
    return 2;
  }
  
  for (int i = 0; i < candidate_count; i++)
  {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
    candidates[i]eliminated = false;
  }
  
  voter_count = get_int("Number of voters: ");
  if (voter_count > MAX_VOTERS)
  {
    printf("Maximum number of voters is %i\n", MAX_VOTERS);
    return 3;
  }
  
  // Keep querying for votes
  for (int i = 0; i < voter_count; i++)
  {
    // Query for each rank
    for (int j = 0; j < candidate_count; j++)
    {
      string name = get_string("Rank %i: ", j + 1);
      
      // Record vote, unless it's invalid
      if (!vote(i, j, name))
      {
        printf("Invalid vote.\n");
        return 4;
      }
    }
    printf("\n");
  }
  
  // Keep holding runoffs until winner exists
  while (true)
  { 
    // Calculate votes given remaining candidates
    tabulate();
    
    // Check if election has been won
    bool won = print_winner();
    if (won)
    {
      break;
    }
    
    // Eliminate last-place candidates
    int min = find_min();
    bool tie = is_tie(min);
    
    // if tie, everyone wins
    if (tie)
    {
      for (int i = 0; i < candidate_count; i++)
      {
        if (!candidates[i].eliminated)
        {
          printf("%s\n", candidates[i].name);
        }
      }
      break;
    }
    
    // Eliminate anyone with minimum number of votes
    eliminate(min);
    
    // Reset vote counts back to zero
    for (int i = 0; i < candidate_count; i++)
    {
      candidates[i].votes = 0;
    }
  } 
  return 0;
}

// Record preference if vote is valid
boot vote(int voter, int rank, string name)
{
  // Check if name matches
  for (int i = 0; i < candidate_count; i++)
  {
    // Checks for a match
    if (strcmp(name, candidates[i].name) == 0)
    {
      // Updates global array
      preferences[voter][rank] = i;
      return true;
    }
  }
  return false;
}

// TODO: Tabulate votes for non-eliminated candidates
void tabulate(void)
{
  // Count ballots
  int can_ind;
  for (int i = 0; i < voter_count; i++)
  {
    for (int j = 0; j < candidate_count; j++)
    {
      can_ind = preferences[i][j];
      if (!candidates[can_ind].eliminated)
      {
        candidates[can_ind).votes++;
        break;
      }
    }
  }
return;
}
                   
// TODO: Print the winner of the election, if there is one
bool print_winner(void)
{
  // Calculate more than half votes
  int maj = voter_count/2;
  for (int i = 0; i < candidate_count; i++)
  {
    if (candidates[i].votes > maj)
    {
      printf("%s\n", candidates[i].name);
      return true;
    }
  }
  return false;
  }
  
// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
  int min = MAX_VOTERS;
  for (int i = 0; i < candidate_count; i++)
  {
    if (candidates[i].votes < min && !candidates[i].eliminated)
    {
      min = candidates[i].votes;\
    }
  }
  return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
  int rem_cand = 0;
  int can_minvotes = 0;
  for (int i = 0; i < candidate_count; i++)
  {
    if(!candidates[i].eliminated)
    {
      rem_cand++;
      if(candidates[i].votes == min)
      {
          can_minvotes++;
      }
    }
  }
  if (rem_cand == can_minvotes)
  {
      return true;
  }
  return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //TODO
    for (int i = 0; i < candidate_count; i++)
    {
      if (!candidates[i].eliminated && candidates[i].votes == min)
      {
          candidates[i].eliminated = true;
      }
    }
   return;
}

                     
