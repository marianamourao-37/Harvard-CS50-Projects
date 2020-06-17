// libraries needed:
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool valid_key(int argc, string argv[]); // declaration of the function that tests whether the key is valid or not
void ciphertext(string plaintext,
                string key); // declaration of the function that encrypts the entered text (plaintext) based on the encryption key

int main(int argc, string argv[])
{
    if (!valid_key(argc, argv)) // if the encryption key of isn't valid
    {
        // alerts the user to correctly enter a valid encryption key
        printf("The user should enter an unambiguous key with 26 letters in the command-line, in the following way: ./substitution key\n");
        return 1; // return from main a value of 1 (which tends to signify an error) immediately
    }

    string plaintext = get_string("plaintext: "); // prompts the user to enter a text wished to be encrypted (plaintext)

    ciphertext(plaintext, argv[1]); // encryption of the plaintext, based on the encryption key

    return 0; // program exits by returning 0 from main
}

bool valid_key(int argc, string argv[])
// implementation of the function that analysis if the entered encryption key is valid or not, based on the number (argc) and respective
// strings in the string array (argv[]) specified in the command-line. If is valid returns the bool variable of true, and if is not returns the
// bool variable of false
{
    if (argc !=
        2) // if it was not entered a command-line besides the name of the file to be run (and so it was not provided a encryption key) or
        // it was entered more than one command-line besides the name of the file to be run
    {
        return false; // encryption key isn't valid
    }

    else // if it was entered 2 command-lines (name of the file to be run and supposed encryption key)
    {
        if (strlen(argv[1]) != 26) // if the encryption key provided has not 26 letters
        {
            return false; // encryption key isn't valid
        }

        else // if the  encryption key provided has 26 letters
        {
            int count[26] = {0}; // initialization of the variable to which is going to be assigned the number of times each letter in
            // the alphabet, regardless of its capitalization, it appears in the encryption key

            for (int i = 0; i < 26; i++)
                // for loop that iterates for each character in the encryption key provided, with a total of 26 letters
            {
                if (argv[1][i] >= 'A' && argv[1][i] <= 'z') // if the character is a letter (correct character)
                {
                    count[tolower(argv[1][i]) - 'a'] ++; // increments by 1 the number of times the respective letter appears

                    if (count[tolower(argv[1][i]) - 'a'] > 1) // if the respective letter appears more than once
                    {
                        return false; // encryption key isn't valid
                    }
                }
                else // if the character isn't a letter (invalid character)
                {
                    return false; // encryption key isn't valid
                }
            }
            return true; // if every exclusion condition wasn't verified, the encryption key must be valid (has only letters that appeared just once)
        }
    }
}

void ciphertext(string plaintext, string key)
// implementation of the function that encrypts the entered text (plaintext) based on the key of encryption
{
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
        // for loop that iterates for each character in the plaintext
    {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') // if the character is a letter in uppercase
        {
            printf("%c", toupper(key[tolower(
                                         plaintext[i]) - 'a'])); // maps the letter in plaintext for its corresponding in the encryption key, and converts for uppercase
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') // if the character is a letter in lowercase
        {
            printf("%c", tolower(key[tolower(
                                         plaintext[i]) - 'a'])); // maps the letter in plaintext for its corresponding in the encriptic key, and converts for lowercase
        }
        else // if the character isn't a letter
        {
            printf("%c", plaintext[i]); // prints exactly the character in plaintext (includes for example ',', '.' and ' ')
        }
    }
    printf("\n"); // prints a newline
}
