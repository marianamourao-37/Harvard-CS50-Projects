#include <cs50.h>
#include <stdio.h>
#include <math.h>

void total_last_digit(long card_number, int extension,
                      string card); // identifies if the entered number satisfies the conditions of a specific credit card category, based on Luhn’s algorithm

int main(void)
{
    long number_card = get_long("Enter a credit card number: "); // prompts the user to enter a credit card number 
    long american_exp = number_card / pow(10, 
                                          13); // initialization of the variable that has as assumption that the credit card is American Express (has 15 digits in total), attributing to it the first two most significant digits
    long mastercard = number_card / pow(10, 
                                        14); // initialization of the variable that has as assumption that the credit card is MasterCard (has 16 digits in total), attributing to it the first two most significant digits
    long visa_1 = number_card / pow(10, 
                                    15); // initialization of the variable that has as assumption that the credit card is VISA (has 16 digits in total), attributing to it the first most significant digit
    long visa_2 = number_card / pow(10,
                                    12); // initialization of the variable that has as assumption that the credit card is VISA (has 13 digits in total), attributing to it the first most significant digit

    if (american_exp == 34
        || american_exp == 
        37) // if it has the same lenght as the American Express credit card number and it has the first two most significant digits specific of this category
    {
        total_last_digit(number_card, 15, "AMEX\n"); // check if it really is an American Express credit card, based on Luhn’s algorithm
    }
    else if (visa_2 ==
             4) // if it has the same lenght as the VISA credit card number and it has the first most significant digit specific of this category
    {
        total_last_digit(number_card, 13, "VISA\n"); // check if it really is an VISA credit card, based on Luhn’s algorithm
    }
    else if (mastercard == 51 || mastercard == 52 || mastercard == 53 || 
             mastercard == 54
             || mastercard == 
             55) // if it has the same lenght as the MasterCard credit card number and it has the first two most significant digits specific of this category
    {
        total_last_digit(number_card, 16, "MASTERCARD\n"); // check if it really is an MasterCard credit card, based on Luhn’s algorithm
    }   
    else if (visa_1 == 
             4) // if it has the same lenght as the VISA credit card number and it has the first most significant digit specific of this category
    {
        total_last_digit(number_card, 16, "VISA\n"); // check if it really is an VISA credit card, based on Luhn’s algorithm
    } 
    else // if none of those conditions specified were validated, the number that was given is invalid, for the considered specifications
    {
        printf("INVALID\n"); // identifies that the number entered is invalid 
    }        
}

void total_last_digit(long card_number, int extension, string card)
{
    // function that takes as inputs the number entered by the user (long card_number), its extension (int extension), and the apparent correspondence to the category of credit card considered in this program (string card). It doesn't return any output.

    int sum_underlined = 0; // initialization of the variable that sums the values that are meant to be doubled
    int sum_other = 0; // initialization of the variable that sums the values that are meant to be directly added without multiplication 
    long digit; //creation of the variable that identifies a certain digit 
    long number; //creation of the variable that assigns the number composed of the first i most significant digits of the given number 
    int multiplied; // creation of the variable that will assign the number resulted from the multiplication of the desired digits 

    for (int i = 0; i < extension ; i++) // for every digit in the number 
    {
        number = card_number / pow(10, i); // assignment of the number composed of the first i most significant digits of the given number
        digit = card_number / pow(10, i +
                                  1); // assignment of the number composed of the first i + 1 most significant digits of the given number
        digit = number  - (digit * 10); // digit to be considered in the i position 

        if (i % 2 != 0) // for the digits meant to be doubled 
        {
            multiplied = 2 * digit;
            int st_digit = multiplied / 10; // initialization of the variable that verifies if the number as two digits or one

            if (st_digit == 0) // if the number resulted from the multiplication of the given digit has just 1 digit
            {
                sum_underlined += multiplied; // direct addition 
            }
            else // if the number resulted from the multiplication of the given digit has 2 digits (maximum)
            {
                sum_underlined += st_digit + (multiplied - (st_digit *
                                              10)); // separate addition of the two digits that compose the number resulted from the multiplication of the given digit
            }
        }
        else // if the given digit isn't supposed to be multiplied 
        {
            sum_other += digit; // direct addition 
        }
    }

    if ((sum_underlined + sum_other) % 10 == 
        0) // if the number is multiple of 10, and consequently its least significant number is equal to 0 
    {
        printf("%s", card); // identifies the category of the credit card number entered 
    }
    else // if the number ins't multiple of 10, and consequently its least significant number ins't equal to 0 
    {
        printf("INVALID\n"); // identifies that the number entered is invalid 
    }
}
