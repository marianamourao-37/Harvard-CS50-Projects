# import libraries:
from cs50 import get_string


def main():
    text = get_string("Enter some text: ")  # prompts the user to enter a text

    # initialization of variables:
    words = 0  # counts the number of words
    sentences = 0  # counts the number os sentences
    letters = 0  # counts the number of letters

    # loops over all the characters in the given text
    for character in text:
        if character.isalpha():  # if the character is alphabetic
            letters += 1
        elif character == " ":  # if the character is a blanck space
            words += 1
        elif character == "!" or character == "?" or character == ".":  # characters that indicates the end of a sentence
            sentences += 1

    if letters != 0:  # if the text entered by the user has at least 1 character
        # actualizes the correct number of words in the given text by considering that for i spaces between words exists i+1 words
        words += 1

    letters_per100 = (letters * 100) / words  # assignment of the average number of characters per 100 words in the given text

    sentences_per100 = (sentences * 100) / words  # assignment of the average number of senteces per 100 words in the given text

    # assignment of the grade determined by the Coleman-Liau's algorithm
    grade = Coleman_Liau_index(letters_per100, sentences_per100)

    # printing of the grade:
    if grade < 1:
        print("Before Grade 1")

    elif grade >= 16:
        print("Grade 16+")

    else:
        print(f"Grade {grade}")


def Coleman_Liau_index(num_letters_per100, sentences_per100):
    # implementation of the function that calculates the Coleman-Liau index, based on the number of characters and sentences per 100 words in the given text
    return round(0.0588 * num_letters_per100 - 0.296 * sentences_per100 - 15.8)  # rounds to an integer the Coleman-Liau index


main()
