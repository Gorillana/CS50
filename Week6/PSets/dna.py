# Compare DNA subsequences in a csv file

import csv
import sys

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Error! Usage: python dna.py database/file.csv sequences/#.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    # Create list to add rows into from csv file
    database = []
    with open(sys.argv[1], 'r') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as txtfile:
        dna_sequence = txtfile.read()

    # TODO Find longest match of each STR in DNA sequence
    # Use list of keys to isolate key/subseq results after 'name'
    subsequences = list(database[0].keys())[1:]

    # Create dicitonary for subsequence matches
    submat = {}
    for subsequence in subsequences:
        submat[subsequence] = longest_match(dna_sequence, subsequence)

    # TODO: Check database for matching profiles
    for person in database:
        match = 0
        for subsequence in subsequences:
            if int(person[subsequence]) == submat[subsequence]:
                match += 1

    # If subsequences match when reading through file, return person that matches
      if match == len(subsequences):
          print(person["name"])
          return

    print("No match")

    return


def longest_match(sequence, subsequence):
    """ Returns lengths of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of chars) w/in sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

           # If there is no match in the substring
            else:
                break

          # Update most consecutive matches found
          longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence return longest run found
    return longest_run

main()
