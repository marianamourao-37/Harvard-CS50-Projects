// libraries included:
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
const int MAX = 9; // maximum number of candidates that an election can have

// Candidates have name and vote count
typedef struct
{
    string name; // field to which is going to be associated the name of the candidate
    int votes; // field to which is going to be associated the total number of votes on the respective candidate
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
        return 1; // exits the program
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    if (candidate_count > MAX) // if the number of different candidates is higher than the maximum permitted
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2; // exits the program
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; // (i+1)th name in the string array entered in the command-line (excluding the first string
        // correspondent to the command-line for the program to run)

        candidates[i].votes = 0; // initialization of the number of votes for the ith candidate
    }

    int voter_count = get_int("Number of voters: "); // prompts the user to enter the total number of voters

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: "); // prompts the user to enter the vote

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Loop over all voters until it reaches the name match to what was entered by the user (input name of the current function)
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i].name, name)) // name match
        {
            candidates[i].votes ++; // increment by 1 the number of votes to the corresponding candidate
            return true; // sinalization that it was found a name match (valid input name)
        }

        // continue the search until it analyses every candidate in the candidates array
    }
    return false; // sinalization that it wasn't found a name match (invalid input name)
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winner_vote =
        candidates[0].votes; // initialization of the variable to which is assign the highest number of votes, currently assuming
    // that it belongs to the first candidate

    // loop over all candidates excluding the first one, that establish the initial value of the highest number of votes
    // implementation of linear search algorithm for finding the highest number of votes

    for (int i = 1; i < candidate_count; i++)
    {
        if (winner_vote < candidates[i].votes)
        {
            winner_vote = candidates[i].votes; // reassignment of the current higher number of votes

        }
    }

    // loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == winner_vote) // if the number of votes on the ith candidate equals the highest number of votes register
        {
            printf("%s\n", candidates[i].name); // print the ith candidate's name
        }
    }
    return;
}
