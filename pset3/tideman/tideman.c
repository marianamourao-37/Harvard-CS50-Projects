#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser. each pair includes the winner’s candidate index and the loser’s candidate index.
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX]; // array of strings representing the names of each of the candidates
pair pairs[MAX * (MAX - 1) / 2]; // array of pairs, which will represent all of the pairs of candidates
//(for which one is preferred over the other) in the election

// global variables
int pair_count; // number of pairs in the array pairs
int candidate_count; // number of candidates in the array candidates
int count = 0;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void merge(pair arr[], int left, int mid, int right);
void merge_sort(pair arr[], int left, int right);
bool validate_edge(int winner_cycle, int winner_check);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1]; // (i+1)th name in the string array entered in the command-line (excluding the first string
        // correspondent to the command-line for the program to run)
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false; // loops through the locked graph and initially sets all of the values to false
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: "); // prompts the user to enter the total number of voters

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1); // ranks[i] is the index of the candidate who is the ith preference for the voter.

            // Check for invalid vote
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks); // update the global preferences variable

        printf("\n");
    }

    add_pairs(); // pairs of candidates are added to the pairs array
    sort_pairs(); // votes sorted via a call to sort_pairs
    lock_pairs(); // locked into the graph via a call to lock_pairs
    print_winner();  // print out the name of the election’s winner
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Loop over all voters until it reaches the name match to what was entered by the user (input name of the current function)
    for (int i = 0; i < candidate_count; i ++)
    {
        if (!strcmp(candidates[i], name)) // name match
        {
            ranks[rank] = i;
            return true; // sinalization that it was found a name match (valid input name)
        }
        // continue the search until it analyses every candidate in the candidates array
    }
    return false; // sinalization that it wasn't found a name match (invalid input name)
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // loop over all candidates
    for (int i = 0; i < candidate_count; i ++)
    {
        // loop over all candidates that were least ranked in relation to the ith candidate
        for (int j = i + 1; j < candidate_count; j ++)
        {
            preferences[ranks[i]][ranks[j]] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // loop over all candidates
    for (int i = 0; i < candidate_count; i ++)
    {
        // loop over all candidates respective to the preferences' superior diagonal matrix (for skipping repetitive calculations,
        // because this loop will atualize the enteries of the preferences' lower diagonal matrix)
        for (int j = i + 1; j < candidate_count; j ++)
        {
            // atualizes the pairs array, identifying for each pair the winner and the loser, atualizing the global variable
            // counting the total number of pairs. if the candidates that are being compared are tied, they dont account for a pair
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count ++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // calls the merge sort algorithm for sorting in descending order the pairs in the pairs array
    merge_sort(pairs, 0, pair_count - 1);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // loop over all pairs
    for (int i = 0; i < pair_count; i ++)
    {
        // considers that edge corresponding to the ith pair doesn't create a cycle
        locked[pairs[i].winner][pairs[i].loser] = true;

        if (validate_edge(pairs[i].winner, pairs[i].winner) == false) // checks if the ith pair doesnt create a cycle
        {
            locked[pairs[i].winner][pairs[i].loser] = false; // if the ith pair creates a cycle n the graph, remove the edge
        }
        count = 0; // sets to 0 the global variable

    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // iterates over the rows of locked 2-dimensional array (matrix)
    for (int i = 0; i < candidate_count; i++)
    {
        // initialization of the variable to which is assign the number of edges that aren't pointing towards him
        int counter = 0;

        // iterates over the columns of locked 2-dimensional array (matrix)
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if the jth candidate has a edge pointing towards the ith candidate (jth candidate wins over ith candidate)
            if (!locked[j][i])
            {
                // if false, increment the counter by 1
                counter ++;
            }
        }
        // if the ith candidate has no edge pointing towards him, it most the source (or one of them) of the graph
        if (counter == candidate_count)
        {
            printf("%s\n", candidates[i]); // print the ith candidate's name (winner)
        }
    }
    return;
}

void merge_sort(pair arr[], int left, int right)
{
    if (left < right) // check correctness of the initial and last index of an array (initial must be lower than the last)
    {
        int mid = left + (right - left) / 2; // mid index of the pairs array to be considered

        merge_sort(arr, left, mid); // merge left half of the pairs array to be considered
        merge_sort(arr, mid + 1, right); // merge right half of the pairs array to be considered
        merge(arr, left, mid, right); // merge left and right halfs with each other
    }
}

void merge(pair arr[], int left, int mid, int right)
{

    int nleft = mid - left + 1; // lenght of the left array being considered

    int nright =  right - mid; // lenght of the right array being considered

    pair l[nleft], r[nright]; // creation of l a r arrays (with the respective lenght) with fields sepecified in the definition of pair

    // clone of the pairs array left half into l array
    for (int i = 0; i < nleft; i++)
    {
        l[i] = arr[left + i];
    }

    // clone of the pairs array right half into r array
    for (int j = 0; j < nright; j++)
    {
        r[j] = arr[mid + 1 + j];
    }

    int i = 0; // initial search index of the left half
    int j = 0; // initial search index of the right half

    int k = left; // lower index of the arrays being sorted

    // merges the right and left halfs
    while (i < nleft && j < nright) // loops until it hasn't passed the length of one of the arrays being merged
    {
        if (preferences[l[i].winner][l[i].loser] > preferences[r[j].winner][r[j].loser]) //ith element of left half higher than jth
            // element of right half
        {
            arr[k] = l[i]; // sorts the ith element
            i ++; // incremention by 1 the index of search of the left half array, excluding from the merge the already sorted element
        }
        else //ith element of left half equal or lower than jth element of right half
        {
            arr[k] = r[j]; // sorts the jth element
            j ++; // incremention by 1 the index of search of the right half array, excluding from the merge the already sorted element
        }
        k ++;
    }

    while (i < nleft) // if the elements of the left half haven't been all sorted, sort until is passed the left half length
    {
        arr[k] = l[i]; // sorts the ith element
        i++; // incremention by 1 the index of search of the left half array, excluding from the merge the already sorted element
        k++;
    }

    while (j < nright) // if the elements of the right half haven't been all sorted, sort until is passed the right half length
    {
        arr[k] = r[j]; // sorts the jth element
        j++; // incremention by 1 the index of search of the right half array, excluding from the merge the already sorted element
        k++;
    }
}

bool validate_edge(int winner_cycle, int winner_check)
{
    if (count != 0 && winner_cycle == winner_check) // if it isnt the fisrt call of this function respective to the winner_check input
        // (where winner_cycle == winner_check), and if you followed the path of successive victories (winner_cycle) in such a way that you returned
        // to the initial stage (winner_check), it means that the edge corresponding to winner_check forms a cycle
    {
        count = -1; // sinalization that the edge considered creates a cycle
        return false;
    }

    else // if it isnt detected a cycle
    {
        // loop over all candidates
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][winner_cycle]) // if the winner being considered loses for other candidate
            {
                validate_edge(i, winner_check); // check if the ith candidate contributes for a cycle path (recursion), by
                // losing for other candidate
            }

            if (count != -1) // if it hasn't been already detected a cycle
            {
                count ++;
            }
        }

        if (count == -1) // after concluding the for cycle, if it has been detected a cycle
        {
            return false;
        }
        else // after concluding the for cycle, if it hasn't been detected a cycle
        {
            return true;
        }
    }
}