// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "dictionary.h"

int totalwords = 0; // initialization of the number of words in the dictionary

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 145000;

// Hash table, initializing to NULL
node *table[N] = {NULL};

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // create a node checker and points towards the st node at the hash(word) position in the hash table
    node *check_word = table[hash(word)];

    while (check_word != NULL) // until it wasn't found a match and the respective linked list wasn't all checked
    {
        // if the word in the given text matches a word in the respetive linked list of the hash table dictionary
        if (strcasecmp(check_word->word, word) == 0)
        {
            return true; // match found
        }

        check_word = check_word->next; // go to the next node in the respective linked list for the posterior match analysis
    }

    return false; // word in the given text doesn't exist in the dictionary
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Adapted by Neel Mehta from
    //http://stackoverflow.com/questions/2571683/djb2-hash-function.

    unsigned long hash = 5381; // initialazation

    for (const char *letter = word; *letter != '\0'; letter ++) // for each letter in the word
    {
        // hash = hash * 33 + letter, altering the letter to a lower case one, because every letter on the dictionary is, by option, lower case
        hash = ((hash << 5) + hash) + tolower(*letter);
    }

    // maps the hash to hash % N, for guarantee that the output index to the hash table doesnt transpasses the maximum number of linked
    // lists (given by N)
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r"); // creates a file (dict) and opens for reading

    if (dict == NULL) // if an error occurred
    {
        return false; // exit
    }

    // creates an array of chars with length LENGTH + 1 (counting for the null terminator and the maximum word extension on the dictionary)
    char word_insert[LENGTH + 1];

    // assigns to the variable word_insert strings of a 46 width maximum, contained on the file dict
    while (fscanf(dict, "%46s", word_insert) != EOF)
    {
        totalwords ++; // actualizes the number of words in the dictionary

        // index on the hash table (given by the hash function) to which is going to be linked the word_insert
        unsigned int index_hash = hash(word_insert);

        node *word_table = malloc(sizeof(node)); // allocates memory for the respective node to be linked on the hash table

        if (word_table == NULL) // if an error occured
        {
            return false; // exit
        }

        strcpy(word_table->word, word_insert); // copies the word_insert to the word field on the node

        // inserts at the beginning of the linked list the created node (order of the preexisting nodes isn't to be conserved nor sorted)
        word_table->next = table[index_hash];
        table[index_hash] = word_table;
    }

    fclose(dict); // closes the file dict
    return true; // successful loading
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return totalwords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *temp = NULL; // initialization of a temporary node that deletes the node on the hash table
    node *cursor = NULL; // initialization of a cursor that prevents leaked memory

    for (int i = 0; i < N; i ++) // loops over all the linked lists in the hash table
    {
        cursor = table[i]; // cursor points towards what the ith entery of the hash table is pointing

        if (cursor != NULL) // if it exists an linked list
        {
            temp = cursor; // temp points towards the st node on the linked list
            while (cursor->next != NULL) // until the end of the linked list, perfom the following:
            {
                cursor = cursor->next; // cursor points towards the next node
                free(temp); // frees the memory associated to the previous node
                temp = cursor; // temp points towards the next node
            }
            free(cursor); // frees the memory associated to the last node in the linked list
        }
    }
    return true; // successful unloading
}
