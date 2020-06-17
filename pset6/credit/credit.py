# imported libraries
from cs50 import get_string
import re


def main():
    number_card = get_string("Enter a credit card number: ")  # prompts the user for a credit card number

    # if it has the same lenght as the American Express credit card number and it has the first two most significant digits specific of this category
    if (re.search("^34", number_card) or re.search("^37", number_card)) and len(number_card) == 15:
        total_last_digit(number_card, "AMEX\n")  # check if it really is an American Express credit card, based on Luhn’s algorithm

    # if it has the same lenght as the VISA credit card number and it has the first most significant digit specific of this category
    elif re.search("^4", number_card) and (len(number_card) == 16 or len(number_card) == 13):
        total_last_digit(number_card, "VISA\n")  # check if it really is an VISA credit card, based on Luhn’s algorithm

    # if it has the same lenght as the MasterCard credit card number and it has the first two most significant digits specific of this category
    elif (re.search("^51", number_card) or re.search("^52", number_card) or re.search("^53", number_card) or re.search("^54", number_card) or
          re.search("^55", number_card)) and len(number_card) == 16:
        total_last_digit(number_card, "MASTERCARD\n")  # check if it really is an MasterCard credit card, based on Luhn’s algorithm

    else:  # if none of those conditions specified were validated, the number that was given is invalid, for the considered specifications
        print("INVALID")  # identifies that the number entered is invalid


def total_last_digit(number_card, card):
    sum_underlined = 0  # initialization of the variable that sums the values that are meant to be doubled
    sum_other = 0  # initialization of the variable that sums the values that are meant to be directly added without multiplication

    # for every digit in the number, starting from the least significant one
    for n in range(-1, -len(number_card) - 1, -1):
        if int(n + 1) % 2 == 0:  # if the given digit isn't supposed to be multiplied
            sum_other += int(number_card[n])  # direct addition

        else:  # for the digits meant to be doubled
            number = 2 * int(number_card[n])

            if number >= 10:  # if the number resulted from the multiplication of the given digit has 2 digits (maximum)
                # separate addition of the two digits that compose the number resulted from the multiplication of the given digit
                number = 1 + (number - 10)

            sum_underlined += number

    if (sum_underlined + sum_other) % 10 == 0:  # if the number is multiple of 10, and consequently its least significant number is equal to 0
        print(card)  # identifies the category of the credit card number entered

    else:  # if the number ins't multiple of 10, and consequently its least significant number ins't equal to 0
        print("INVALID")  # identifies that the number entered is invalid


main()