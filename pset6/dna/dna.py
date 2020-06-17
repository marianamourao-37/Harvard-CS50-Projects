# imported libraries:
from sys import argv, exit
import csv
import re


def main():
    if len(argv) < 3:  # if it wasn't entered the dna file and sequence file
        print("Usage: python dna.py data.csv sequence.txt")  # alerts the user for appropriate usage of the program
        exit(1)  # exits the program

    with open(argv[1], "r") as str_file:  # opens for reading the str database
        database_str = csv.reader(str_file, delimiter=",")

        i = 0  # variable for reading the first line

        # loops over all the rows in the str database
        for row in database_str:
            if i == 0:  # if it is the first line
                strs = row[1:]  # strs as the second to last columns names in the csv file

                # calls a function that counts the maximum number of consecutive STRs sequences in the given DNA sequence
                list_match_str = num_match_str(strs, argv[2])
                i = 1  # first line is read

            else:  # loops over all the individuals on the str database
                found_match = match_occurrence(row, list_match_str)  # calls a function that verifies if exist a match

                if found_match:  # if a match was found
                    print(row[0])  # prints the person's name
                    exit(0)  # exits the program

    print("No match")  # it wasn't found a match
    exit(0)  # exits the program


# counts the maximum number of consecutive STRs sequences in the given DNA sequence
def num_match_str(strs, dna_sequence):
    # strs -> array qith the STRs
    # dna_sequence -> name of the DNA sequence text file

    str_matches = []  # creates an array for storing the number of STRs

    with open(dna_sequence, "r") as sequence:  # opens for reading the DNA sequence text
        text = sequence.read()  # reads into the variable text

    # loops over all the strs
    for str in strs:
        maximum = 0  # initializes the maximum number of consecutives times the given str appears
        counts = 0  # initializes the number of consecutives times the given str appears
        i = 0  # variable for iterating over the DNA sequence text array
        limit = len(text) - len(str)  # limit for the lower index of an array of size = len(str), without an segmentation fault

        # loops over the DNA sequence text array
        while i <= limit:
            if text[i: i + len(str)] == str:  # if
                counts += 1  # actualizes the counter for the beginning of a new consecutive series of str sequences
                i = i + len(str) + (counts - 1) * len(str)  # next lower index
                loop = True  # allows the analysis for consecutive STR sequences

                # analysis for consecutive STR sequences
                while i <= limit and loop:
                    if re.search("^" + str, text[i:]):  # if was found a consecutive STR sequence
                        counts += 1  # increments the counter
                        i += len(str)  # next lower index
                    else:  # checks if the counter for the consecutive STR sequences is higher than the previous maximum
                        if counts > maximum:
                            maximum = counts
                        counts = 0  # resets the counter for the analysis of other consecutive series of str sequences
                        loop = False  # breaks this while loop
            else:
                i += 1  # next lower bound

        str_matches.append(maximum)  # sets the maximum number of consecutive sequences for the given str

    return str_matches  # returns an array that has the maximum number of consecutive sequences for the given strs


# verifies if exist a match
def match_occurrence(individual, list_match_str):
    # individual -> array that contains their name and str's counts
    # list_mach_str -> str's counts in the given DNA sequence

    # loops over all the str's counts
    for n in range(len(list_match_str)):
        if int(individual[n+1]) != list_match_str[n]:  # if for the nth str count it wasn't corresponded
            return False  # a match for the individual wasn't found

    return True  # if a match was verified in all the str's counts


if __name__ == "__main__":
    main()
