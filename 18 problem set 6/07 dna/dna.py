import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1

    # TODO: Read database file into a variable
    database_f = open(sys.argv[1])
    db_reader = csv.DictReader(database_f)

    # TODO: Read DNA sequence file into a variable
    DNA_sequence_f = open(sys.argv[2])
    DNA_sequence = DNA_sequence_f.read()
    DNA_sequence_f.close()

    # TODO: Find longest match of each STR in DNA sequence
    STRs = db_reader.fieldnames[1:]
    longest = {}
    for STR in STRs:
        longest[STR] = longest_match(DNA_sequence, STR)

    # TODO: Check database for matching profiles
    for row in db_reader:
        match = True
        for STR in STRs:
            if longest[STR] != int(row[STR]):
                match = False
                break
        if match:
            print(f"{row['name']}")
            database_f.close()
            return
    print("No match")
    database_f.close()
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
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

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
